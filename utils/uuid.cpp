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

#include "uuid.h"
#include <QUuid>
static QString uuid_null("00000000-0000-0000-0000-000000000000");

QString Uuid::null()
{
    // need to change because it has curly brackets.
    return QUuid().toString();
}

bool Uuid::isNull(QString uuid)
{
    return uuid_null == uuid;
}

QString Uuid::generate()
{
    return QUuid::createUuid().toString();
}
