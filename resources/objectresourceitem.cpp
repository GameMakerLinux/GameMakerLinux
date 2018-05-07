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
}

QJsonObject ObjectResourceItem::save()
{
    QJsonObject object;
    object["id"] = id();
/*
{
    "id": "e6955b21-1ff0-456b-8b55-4a4e7f4c0bf3",
    "modelName": "GMObject",
    "mvc": "1.0",
    "name": "obj_enemy_behind_left",
    "eventList": [
        {
            "id": "03bf3b5a-00ed-4df5-be63-29d48351f2f8",
            "modelName": "GMEvent",
            "mvc": "1.0",
            "IsDnD": false,
            "collisionObjectId": "00000000-0000-0000-0000-000000000000",
            "enumb": 73,
            "eventtype": 8,
            "m_owner": "e6955b21-1ff0-456b-8b55-4a4e7f4c0bf3"
        }
    ],
    "maskSpriteId": "00000000-0000-0000-0000-000000000000",
    "overriddenProperties": null,
    "parentObjectId": "129c4145-87b0-4911-bb13-e558733d672a",
    "persistent": false,
    "physicsAngularDamping": 0.1,
    "physicsDensity": 0.5,
    "physicsFriction": 0.2,
    "physicsGroup": 0,
    "physicsKinematic": false,
    "physicsLinearDamping": 0.1,
    "physicsObject": false,
    "physicsRestitution": 0.1,
    "physicsSensor": false,
    "physicsShape": 1,
    "physicsShapePoints": null,
    "physicsStartAwake": true,
    "properties": null,
    "solid": false,
    "spriteId": "76e40821-6926-4152-8ebb-6d9a03de7e44",
    "visible": true
}
*/
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
