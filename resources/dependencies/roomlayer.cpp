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

#include "roomlayer.h"

RoomLayer::RoomLayer(ResourceType type)
    : ResourceItem(type)
{
}

int RoomLayer::depth() const
{
    return m_depth;
}

void RoomLayer::setDepth(int d)
{
    m_depth = d;
}

void RoomLayer::load(QJsonObject object)
{
    id = object["id"].toString();
    setName(object["name"].toString());
    setDepth(object["depth"].toInt());
}