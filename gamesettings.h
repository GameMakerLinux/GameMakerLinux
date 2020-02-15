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

#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QString>

class GameSettings
{
public:
    GameSettings() = delete;

    static QString rootPath();
    static void setRootPath(QString root);

    static QString lastOpenedProject();
    static void setLastOpenedProject(QString filename);

    static void save();
    static void load();

private:
    static QString root_path;
    static QString last_opened_project;
};

#endif // GAMESETTINGS_H
