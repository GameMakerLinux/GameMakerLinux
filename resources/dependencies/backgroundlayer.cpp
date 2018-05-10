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
#include <QVariant>

BackgroundLayer::BackgroundLayer()
    : RoomLayer { ResourceType::BackgroundLayer }
{
}

void BackgroundLayer::load(QJsonObject object)
{
    RoomLayer::load(object);

    m_spriteId = object["spriteId"].toString();

    auto colourJson = object["colour"].toObject();
    auto colourValue = colourJson["Value"].toVariant().toUInt();
    int r = colourValue & 0xFF;
    int g = (colourValue >> 8) & 0xFF;
    int b = (colourValue >> 16) & 0xFF;
    int a = (colourValue >> 24) & 0xFF;
    m_colour = QColor(r, g, b, a);
}

SpriteResourceItem *BackgroundLayer::sprite() const
{
    if (!Uuid::isNull(m_spriteId))
    {
        return ResourceItem::get<SpriteResourceItem>(m_spriteId);
    }
    return nullptr;
}

QColor BackgroundLayer::colour() const
{
    return m_colour;
}
