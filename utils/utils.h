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

#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class Utils
{
public:
    Utils() = delete;

    static QJsonObject readFileToJSON(QString filename);
    static QString readFile(QString filename);
    static QString getEventName(int eventType, int eventNumber);
    static QString getEventFileName(int eventType, int eventNumber);
};

#endif // UTILS_H
