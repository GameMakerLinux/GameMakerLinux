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

#ifndef TILESETRESOURCEITEM_H
#define TILESETRESOURCEITEM_H

#include "resourceitem.h"
#include "spriteresourceitem.h"
#include <QSize>

class TileSetResourceItem : public ResourceItem
{
    Q_OBJECT

public:
    TileSetResourceItem();

    void load(QJsonObject object) override;
    void initialize() override;

    int tileWidth() const;
    int tileHeight() const;
    QPixmap getTile(uint32_t id) const;

private:
    QSize m_tileSize;
    int m_tileCount;
    SpriteResourceItem * m_sprite;

    QString m_spriteId;
};

#endif // TILESETRESOURCEITEM_H
