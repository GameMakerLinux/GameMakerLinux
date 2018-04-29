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

#include "utils.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>

QJsonObject Utils::readFileToJSON(QString filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly))
    {
        qCritical() << "Can't open file" << filename;
        return {};
    }

    QJsonParseError error;
    auto doc = QJsonDocument::fromJson(f.readAll(), &error);
    f.close();

    if (error.error != QJsonParseError::NoError)
    {
        qCritical() << "JSON error:" << error.errorString();
        return {};
    }

    return doc.object();
}

QString Utils::readFile(QString filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly))
    {
        qCritical() << "Can't open file" << filename;
        return {};
    }

    auto str = f.readAll();
    f.close();

    return str;
}

static const char * eventsTypes[] = {
    "Create",
    "Step",
    "Alarm",
    "Step",
    "4",
    "5",
    "6",
    "Other",
    "Draw",
    "9",
    "10",
    "11",
    "CleanUp"
};
constexpr int EVENTS_COUNT = 13;

QString Utils::getEventName(int eventType, int eventNumber)
{
    if (eventType < EVENTS_COUNT)
    {
        return QString(eventsTypes[eventType]) + (eventType == 0 ? "d" : "");
    }

    return QString("invalid");
}

QString Utils::getEventFileName(int eventType, int eventNumber)
{
    if (eventType < EVENTS_COUNT)
    {
        return QString("%1_%2").arg(eventsTypes[eventType]).arg(eventNumber);
    }

    return QString("invalid_%1_%2").arg(eventType).arg(eventNumber);
}
