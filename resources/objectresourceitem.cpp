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

#include "objectresourceitem.h"
#include <QJsonArray>
#include "utils/uuid.h"
#include "utils/utils.h"
#include "dependencies/objectevent.h"
#include "spriteresourceitem.h"
#include "gamesettings.h"

ObjectResourceItem::ObjectResourceItem()
    : ResourceItem { ResourceType::Object }
{
}

void ObjectResourceItem::load(QJsonObject object)
{
    setName(object["name"].toString());

    auto evList = object["eventList"].toArray();
    for (const auto & value : evList)
    {
        auto json = value.toObject();
        auto event = new ObjectEvent(json);

        eventsList.push_back(event);
    }

    m_maskSpriteId = object["maskSpriteId"].toString();
    m_parentObjectId = object["parentObjectId"].toString();
    m_spriteId = object["spriteId"].toString();

    m_persistent = object["persistent"].toBool();
    m_physicsAngularDamping = object["physicsAngularDamping"].toDouble();
    m_physicsDensity = object["physicsDensity"].toDouble();
    m_physicsFriction = object["physicsFriction"].toDouble();
    m_physicsGroup = object["physicsGroup"].toInt();
    m_physicsKinematic = object["physicsKinematic"].toBool();
    m_physicsLinearDamping = object["physicsLinearDamping"].toDouble();
    m_physicsObject = object["physicsObject"].toBool();
    m_physicsRestitution = object["physicsRestitution"].toDouble();
    m_physicsSensor = object["physicsSensor"].toBool();
    m_physicsShape = object["physicsShape"].toInt();
    m_physicsStartAwake = object["physicsStartAwake"].toBool();
    m_solid = object["solid"].toBool();
    m_visible = object["visible"].toBool();
}

QJsonObject ObjectResourceItem::save()
{
    QJsonObject object;
    object["id"] = id();
    object["modelName"] = Utils::resourceTypeToString(type());
    object["mvc"] = "1.0";
    object["name"] = name();

    QJsonArray events;
    for (auto & event : eventsList)
    {
        events.append(event->pack());
    }
    object["eventList"] = events;

    object["maskSpriteId"] = m_maskSpriteId;
    object["overriddenProperties"] = QJsonValue();
    object["parentObjectId"] = m_parentObjectId;
    object["persistent"] = m_persistent;
    object["physicsAngularDamping"] = m_physicsAngularDamping;
    object["physicsDensity"] = m_physicsDensity;
    object["physicsFriction"] = m_physicsFriction;
    object["physicsGroup"] = m_physicsGroup;
    object["physicsKinematic"] = m_physicsKinematic;
    object["physicsLinearDamping"] = m_physicsLinearDamping;
    object["physicsObject"] = m_physicsObject;
    object["physicsRestitution"] = m_physicsRestitution;
    object["physicsSensor"] = m_physicsSensor;
    object["physicsShape"] = m_physicsShape;
    object["physicsShapePoints"] = QJsonValue();
    object["physicsStartAwake"] = m_physicsStartAwake;
    object["properties"] = QJsonValue();
    object["solid"] = m_solid;
    object["spriteId"] = m_spriteId;
    object["visible"] = m_visible;

    return object;
}

int ObjectResourceItem::eventsCount() const
{
    return eventsList.size();
}

ObjectEvent * ObjectResourceItem::getEvent(int id) const
{
    return eventsList[id];
}

ObjectResourceItem *ObjectResourceItem::parentObject() const
{
    if (!Uuid::isNull(m_parentObjectId))
        return qobject_cast<ObjectResourceItem*>(ResourceItem::get(m_parentObjectId));
    return nullptr;
}

void ObjectResourceItem::setParentObject(ObjectResourceItem * object)
{
    if (object)
        m_parentObjectId = object->id();
    else
        m_parentObjectId = Uuid::null();
}

SpriteResourceItem *ObjectResourceItem::sprite() const
{
    if (!Uuid::isNull(m_spriteId))
        return qobject_cast<SpriteResourceItem*>(ResourceItem::get(m_spriteId));
    return nullptr;
}

void ObjectResourceItem::setSprite(SpriteResourceItem * sprite)
{
    if (sprite)
        m_spriteId = sprite->id();
    else
        m_spriteId = Uuid::null();
}

SpriteResourceItem *ObjectResourceItem::maskSprite() const
{
    if (!Uuid::isNull(m_maskSpriteId))
        return qobject_cast<SpriteResourceItem*>(ResourceItem::get(m_maskSpriteId));
    return nullptr;
}

void ObjectResourceItem::setMaskSprite(SpriteResourceItem * sprite)
{
    if (sprite)
        m_maskSpriteId = sprite->id();
    else
        m_maskSpriteId = Uuid::null();
}

QString ObjectResourceItem::filename() const
{
    return QString("objects/%1/%1.yy").arg(name());
}
