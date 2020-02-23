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

#include "tilelayer.h"
#include "resources/tilesetresourceitem.h"
#include "utils/uuid.h"
#include <QPixmap>

TileLayer::TileLayer()
    : RoomLayer { ResourceType::TileLayer }
{
}

void TileLayer::load(QJsonObject object)
{
    RoomLayer::load(object);

    auto tilesetId = object["tilesetId"].toString();

    if (!Uuid::isNull(tilesetId))
    {
        tilesetItem = ResourceItem::get<TileSetResourceItem>(tilesetId);
    }
}

QPixmap TileLayer::render() const
{
    return QPixmap();
}
