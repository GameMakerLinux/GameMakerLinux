/*
    Copyright (C) Alexander Roper

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "roomresourceitem.h"
#include "dependencies/roomlayer.h"
#include "dependencies/folderlayer.h"
#include "utils/utils.h"
#include "utils/uuid.h"
#include <QJsonArray>

RoomResourceItem::RoomResourceItem()
    : ResourceItem { ResourceType::Room }
{
}

void RoomResourceItem::load(QJsonObject object)
{
    setName(object["name"].toString());

    auto roomSettings = object["roomSettings"].toObject();
    m_settings.load(roomSettings);

    auto layers = object["layers"].toArray();
    loadSubLayers(nullptr, layers);
}

int RoomResourceItem::height() const
{
    return m_settings.height();
}

int RoomResourceItem::width() const
{
    return m_settings.width();
}

QVector<RoomLayer *> RoomResourceItem::layers() const
{
    return m_layers;
}

void RoomResourceItem::loadSubLayers(FolderLayer * parentLayer, QJsonArray layers)
{
    for (auto value : layers)
    {
        auto layerJson = value.toObject();

        auto layerType = Utils::resourceStringToType(layerJson["modelName"].toString());
        auto id = layerJson["id"].toString();
        auto layer = ResourceItem::create(layerType, id);
        layer->load(layerJson);

        auto roomLayer = qobject_cast<RoomLayer*>(layer);
        Q_ASSERT(roomLayer);
        m_layers.append(roomLayer);

        if (parentLayer)
        {
            parentLayer->addSubLayer(roomLayer);
        }

        if (layerType == ResourceType::FolderLayer)
        {
            if (layerJson.contains("layers"))
            {
                loadSubLayers(qobject_cast<FolderLayer*>(layer), layerJson["layers"].toArray());
            }
        }
    }
}

QString RoomResourceItem::filename() const
{
    return QString("rooms/%1/%1.yy").arg(name());
}
