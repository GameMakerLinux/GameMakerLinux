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
        auto event = value.toObject();
        auto type = event["eventtype"].toInt();
        auto number = event["enumb"].toInt();

        eventsList.push_back(qMakePair(type, number));
    }
}

int ObjectResourceItem::eventsCount() const
{
    return eventsList.size();
}

QPair<int, int> ObjectResourceItem::getEvent(int id) const
{
    return eventsList[id];
}
