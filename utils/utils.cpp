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

enum EventType {
    CreateEvent,
    U0Event,
    AlarmEvent,
    StepEvent,
    U1Event,
    U2Event,
    U3Event,
    OtherEvent,
    DrawEvent,
    U4Event,
    U5Event,
    U6Event,
    CleanUpEvent,
    EVENTS_COUNT
};

static QString eventsTypeFileNames[] = {
    "Create",
    "1",
    "Alarm",
    "Step",
    "4",
    "5",
    "6",
    "Other",
    "Draw",
    "KeyPress",
    "10",
    "11",
    "CleanUp"
};

static QMap<int, QString> eventsTypeNames[] = {
    { { 0, "Created" } },
    { { 0, "1" } },
    { { 0, "Alarm" } },
    {
        { 0, "Step" },
        { 1, "Begin Step" }
    },
    { { 0, "4" } },
    { { 0, "5" } },
    { { 0, "6" } },
    {
        { 0, "Other" },
        { 10, "User Event 0" },
    },
    {
        { 0, "Draw" },
        { 64, "Draw GUI" },
        { 73, "Post Draw" }
    },
    {
        { 0, "Key Press" },
        { 13, "Key Press: Enter" }
    },
    { { 0, "10" } },
    { { 0, "11" } },
    { { 0, "Clean Up" } }
};

QString Utils::getEventName(int eventType, int eventNumber)
{
    if (eventType < EVENTS_COUNT)
    {
        switch (eventType)
        {
        case AlarmEvent:
            return QString("%1 %2").arg(eventsTypeNames[eventType][0]).arg(eventNumber);
        case CreateEvent:
        case U0Event:
        case StepEvent:
        case U1Event:
        case U2Event:
        case U3Event:
        case OtherEvent:
        case DrawEvent:
        case U4Event:
        case U5Event:
        case U6Event:
        case CleanUpEvent:
            if (eventsTypeNames[eventType].contains(eventNumber))
            {
                return QString(eventsTypeNames[eventType][eventNumber]);
            }
        }
    }

    qDebug() << "Unknown:" << eventType << eventNumber;
    return QString("Invalid %1 %2").arg(eventType).arg(eventNumber);
}

QString Utils::getEventFileName(int eventType, int eventNumber)
{
    if (eventType < EVENTS_COUNT)
    {
        return QString("%1_%2").arg(eventsTypeFileNames[eventType]).arg(eventNumber);
    }

    return QString("invalid_%1_%2").arg(eventType).arg(eventNumber);
}
