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

#ifndef TILELAYER_H
#define TILELAYER_H

#include "roomlayer.h"
#include <QPixmap>

class TileSetResourceItem;
class TileLayer : public RoomLayer
{
    Q_OBJECT

public:
    TileLayer();

    void load(QJsonObject object) override;
    void initialize() override;

    QPixmap render();

private:
    TileSetResourceItem * m_tilesetItem = nullptr;
    int m_widthCount;
    int m_heightCount;
    std::vector<uint32_t> m_tiles;
    QPixmap m_rendered;
    bool m_dirty = false;

    QString m_tilesetId;
};

#endif // TILELAYER_H
