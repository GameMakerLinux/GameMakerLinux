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
#include <QJsonArray>

RoomResourceItem::RoomResourceItem()
    : ResourceItem(ResourceType::Room)
{
}

void RoomResourceItem::load(QJsonObject object)
{
    setName(object["name"].toString());

    auto layers = object["layers"].toArray();
    for (const auto & value : layers)
    {
        auto layerJson = value.toObject();

        auto layerType = Utils::resourceStringToType(layerJson["modelName"].toString());
        auto id = object["id"].toString();
        auto layer = ResourceItem::create(layerType, id);
        layer->load(layerJson);

        m_layers.append(static_cast<RoomLayer*>(layer));
/*
        auto spriteId = layer["spriteId"].toString();
        if (!Uuid::isNull(spriteId))
        {
            auto pItem = ResourceItem::get(spriteId);
            if (pItem)
            {
                auto spriteItem = qobject_cast<SpriteResourceItem*>(pItem);
                auto json = Utils::readFileToJSON(spriteItem->filename);
                if (!json.isEmpty())
                {
                    auto imageName = json["frames"].toArray().first().toObject()["id"].toString();
                    auto fullPath = QString("%1/sprites/%2/%3.png").arg(GameSettings::rootPath(), spriteItem->name(), imageName);
                    auto pix = scene.addPixmap(QPixmap(fullPath));
                    pix->setParentItem(gLayer);
                }
            }
        }*/
    }
}

QVector<RoomLayer *> RoomResourceItem::layers() const
{
    return m_layers;
}
