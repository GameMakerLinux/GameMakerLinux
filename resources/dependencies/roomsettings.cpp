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

#include "roomsettings.h"

RoomSettings::RoomSettings()
    : ResourceItem { ResourceType::RoomSettings }
{
}

void RoomSettings::load(QJsonObject object)
{
    setId(object["id"].toString());
    setName(object["name"].toString());

    m_height = object["Height"].toInt();
    m_width = object["Width"].toInt();
    m_inheritRoomSettings = object["inheritRoomSettings"].toBool();
}

int RoomSettings::height() const
{
    return m_height;
}

int RoomSettings::width() const
{
    return m_width;
}
