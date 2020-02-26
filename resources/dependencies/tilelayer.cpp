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
#include <QDebug>
#include <QJsonArray>
#include <QPainter>

TileLayer::TileLayer()
    : RoomLayer { ResourceType::TileLayer }
{
}

void TileLayer::load(QJsonObject object)
{
    RoomLayer::load(object);
    qDebug() << "loading" << id();

    m_tilesetId = object["tilesetId"].toString();

    auto tilesData = object["tiles"].toObject();
    m_widthCount = tilesData["SerialiseWidth"].toInt();
    m_heightCount = tilesData["SerialiseHeight"].toInt();
    auto tilesId = tilesData["TileSerialiseData"].toArray();
    m_tiles.resize(static_cast<size_t>(tilesId.size()));
    std::transform(tilesId.begin(), tilesId.end(), m_tiles.begin(), [](QJsonValue value) {
        return static_cast<uint32_t>(value.toDouble());
    });
}

void TileLayer::initialize()
{
    if (!Uuid::isNull(m_tilesetId))
    {
        m_tilesetItem = ResourceItem::get<TileSetResourceItem>(m_tilesetId);
    }
}

QPixmap TileLayer::render() const
{
    if (m_tilesetItem == nullptr)
    {
        return QPixmap();
    }

    auto tileWidth = m_tilesetItem->tileWidth();
    auto tileHeight = m_tilesetItem->tileHeight();
    QPixmap surface(m_widthCount * tileWidth, m_heightCount * tileHeight);
    surface.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&surface);

    for (int y = 0; y < m_heightCount; y++)
    {
        for (int x = 0; x < m_widthCount; x++)
        {
            auto tileId = m_tiles[static_cast<size_t>(x + y * m_widthCount)];
            if (tileId != 0xFFFFFFFF)
            {
                int x_dst = x * tileWidth;
                int y_dst = y * tileHeight;

                auto tilePix = m_tilesetItem->getTile(tileId);
                painter.drawPixmap(x_dst, y_dst, tilePix);
            }
        }
    }
    painter.end();

    return surface;
}
