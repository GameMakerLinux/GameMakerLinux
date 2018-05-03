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

#ifndef OBJECTEVENT_H
#define OBJECTEVENT_H

#include <QJsonObject>
#include <QString>
#include "utils/uuid.h"

class ObjectEvent
{
public:
    enum EventType {
        CreateEvent,
        DestroyEvent,
        AlarmEvent,
        StepEvent,
        CollisionEvent,
        KeyboardEvent,
        MouseEvent,
        OtherEvent,
        DrawEvent,
        KeyPressEvent,
        KeyReleaseEvent,
        AsyncEvent,
        CleanUpEvent,
        GestureEvent,
        EVENTS_COUNT
    };

    ObjectEvent(EventType type, int number);
    ObjectEvent(QJsonObject object);

    QJsonObject pack();

    QString id() const;
    EventType type() const;
    int number() const;
    QString owner() const;

    static QString getName(EventType eventType, int eventNumber);
    static QString getFileName(EventType eventType, int eventNumber);

private:
    QString m_id;
    // "modelName": "GMEvent",
    // "mvc": "1.0",
    // "IsDnD": false,
    QString m_collisionObjectId = Uuid::null();
    EventType m_eventType;
    int m_eventNumber = 0;
    QString m_owner;
};

#endif // OBJECTEVENT_H
