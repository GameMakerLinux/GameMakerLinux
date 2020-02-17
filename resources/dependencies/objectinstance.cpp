/*
    Copyright (C) Alexander Roper

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

#include "objectinstance.h"
#include "utils/uuid.h"
#include "resources/objectresourceitem.h"
#include <experimental/random>

ObjectInstance::ObjectInstance()
    : ResourceItem { ResourceType::ObjectInstance }
{
}

ObjectInstance::ObjectInstance(ObjectResourceItem * item)
    : ObjectInstance()
{
    setId(Uuid::generate());
    ResourceItem::registerItem(id(), this);

    auto num = std::experimental::randint(0x00'00'00'00u, 0xFF'FF'FF'FFu);
    setName(QString("inst_") + QString("%1").arg(num, 8, 16, QChar('0')).toUpper());

    m_objId = item->id();
}

void ObjectInstance::load(QJsonObject object)
{
    setId(object["id"].toString());
    ResourceItem::registerItem(id(), this);

    setName(object["name"].toString());

    setPosition(object["x"].toInt(), object["y"].toInt());

    m_objId = object["objId"].toString();
}

QPoint ObjectInstance::position() const
{
    return m_position;
}

void ObjectInstance::setPosition(int x, int y)
{
    m_position.setX(x);
    m_position.setY(y);
}

ObjectResourceItem *ObjectInstance::object()
{
    if (!Uuid::isNull(m_objId))
        return ResourceItem::get<ObjectResourceItem>(m_objId);
    return nullptr;
}
