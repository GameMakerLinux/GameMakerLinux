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

#ifndef ROOMSETTINGS_H
#define ROOMSETTINGS_H

#include "resources/resourceitem.h"

class RoomSettings : public ResourceItem
{
    Q_OBJECT

public:
    RoomSettings();

    void load(QJsonObject object) override;

    int height() const;
    int width() const;

private:
    int m_width = 0;
    int m_height = 0;
    bool m_inheritRoomSettings = false;
};

#endif // ROOMSETTINGS_H
