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
    : ResourceItem(ResourceType::Object)
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

    m_parentObjectId = object["parentObjectId"].toString();
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

SpriteResourceItem *ObjectResourceItem::sprite() const
{
    if (!Uuid::isNull(m_parentObjectId))
        return qobject_cast<SpriteResourceItem*>(ResourceItem::get(m_spriteId));
    return nullptr;
}

SpriteResourceItem *ObjectResourceItem::maskSprite() const
{
    if (!Uuid::isNull(m_parentObjectId))
        return qobject_cast<SpriteResourceItem*>(ResourceItem::get(m_maskSpriteId));
    return nullptr;
}
