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
#include <type_traits>

#include "resources/resourceitem.h"

class Utils
{
public:
    Utils() = delete;

    // Files
    static QJsonObject readFileToJSON(QString filename);
    static QString readFile(QString filename);
    static bool writeFile(QString filename, QJsonObject object);
    static bool writeFile(QString filename, QByteArray data);

    // Resources
    static QString resourceTypeToString(ResourceType type);
    static ResourceType resourceStringToType(QString type);

    template <typename T>
    static auto enum_cast(T && t)
    {
        return static_cast<std::underlying_type_t<T>>(t);
    }

    enum {
        SortingRole = Qt::UserRole + 1
    };
};

#endif // UTILS_H
