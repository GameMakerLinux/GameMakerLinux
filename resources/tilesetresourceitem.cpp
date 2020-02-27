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

#include "tilesetresourceitem.h"
#include "spriteresourceitem.h"
#include "utils/uuid.h"
#include <QPixmap>

TileSetResourceItem::TileSetResourceItem()
    : ResourceItem { ResourceType::TileSet }
{
}

void TileSetResourceItem::load(QJsonObject object)
{
    setName(object["name"].toString());

    m_spriteId = object["spriteId"].toString();

    m_tileSize.rwidth() = object["tilewidth"].toInt();
    m_tileSize.rheight() = object["tileheight"].toInt();
    m_tileCount = object["tile_count"].toInt();
}

void TileSetResourceItem::initialize()
{
    if (!Uuid::isNull(m_spriteId))
    {
        m_sprite = ResourceItem::get<SpriteResourceItem>(m_spriteId);
    }
}

int TileSetResourceItem::tileWidth() const
{
    return m_tileSize.width();
}

int TileSetResourceItem::tileHeight() const
{
    return m_tileSize.height();
}

int TileSetResourceItem::tileCount() const
{
    return m_tileCount;
}

QPixmap TileSetResourceItem::getTile(uint32_t id) const
{
    auto spritePix = m_sprite->pixmap();
    int tilesPerRow = spritePix.width() / tileWidth();
    int x = static_cast<int32_t>(id) % tilesPerRow;
    int y = static_cast<int32_t>(id) / tilesPerRow;
    return spritePix.copy(x * tileWidth(), y * tileHeight(), tileWidth(), tileHeight());
}
