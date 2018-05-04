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

#include "backgroundlayer.h"
#include "utils/uuid.h"
#include "resources/spriteresourceitem.h"

BackgroundLayer::BackgroundLayer()
    : RoomLayer(ResourceType::BackgroundLayer)
{
}

void BackgroundLayer::load(QJsonObject object)
{
    RoomLayer::load(object);

    auto spriteId = object["spriteId"].toString();
    if (!Uuid::isNull(spriteId))
    {
        m_sprite = ResourceItem::get<SpriteResourceItem>(spriteId);
    }
}

SpriteResourceItem *BackgroundLayer::sprite() const
{
    return m_sprite;
}