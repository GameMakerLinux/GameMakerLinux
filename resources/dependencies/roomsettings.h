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
/*
        "id": "586aef19-2d9b-4e45-b2c7-34d3db3965f5",
        "Height": 720,
        "inheritRoomSettings": false,
        "modelName": "GMRoomSettings",
        "persistent": false,
        "mvc": "1.0",
        "Width": 1280*/
