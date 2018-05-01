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
