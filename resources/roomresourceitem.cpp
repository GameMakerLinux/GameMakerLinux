/*
    Copyright (C) 2018  Alexander Roper

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

    // TODO: replace it with a GMRoomSettings object
    auto roomSettings = object["roomSettings"].toObject();
    m_settings.load(roomSettings);

    auto layers = object["layers"].toArray();
    for (const auto & value : layers)
    {
        auto layerJson = value.toObject();

        auto layerType = Utils::resourceStringToType(layerJson["modelName"].toString());
        auto id = object["id"].toString();
        auto layer = ResourceItem::create(layerType, id);
        layer->load(layerJson);

        m_layers.append(qobject_cast<RoomLayer*>(layer));
    }
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

QString RoomResourceItem::filename() const
{
    return QString("%1/rooms/%2/%2.yy").arg(GameSettings::rootPath(), name());
}
