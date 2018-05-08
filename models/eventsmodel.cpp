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

#include "eventsmodel.h"
#include "resources/objectresourceitem.h"
#include "gamesettings.h"
#include "resources/dependencies/objectevent.h"
#include <QColor>

EventsModel::EventsModel(QObject *parent)
    : QAbstractListModel { parent }
{
}

void EventsModel::addEvent(ObjectEvent * event, bool inherited)
{
    // find if an event with of the same type/number exists
    int eventPosition = findEvent(event->eventType(), event->eventNumber());
    if (eventPosition != -1)
    {
        if (!inherited)
        {
            // if the new one we add is not inherited, remove the existing (inherited) one
            items.remove(eventPosition);
        }
        else
        {
            // if not inherited, don't do anything
            return;
        }
    }

    beginInsertRows(QModelIndex(), items.size(), items.size());
    items.push_back({ event, false, inherited });
    endInsertRows();
}

void EventsModel::clear()
{
    beginResetModel();

    items.clear();

    endResetModel();
}

int EventsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return items.size();
}

QVariant EventsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto & item = items[index.row()];
    auto event = item.event;
    switch (role)
    {
    case Qt::DisplayRole:
        return ObjectEvent::getName(event->eventType(), event->eventNumber()) + (item.modified ? "*" : "");
    case Qt::ForegroundRole:
        if (item.inherited)
            return QColor(Qt::gray);
        break;
    case Utils::SortingRole:
        return Utils::enum_cast(event->type()) * 1000 + event->eventNumber();
    }

    return QVariant();
}

QString EventsModel::getFilename(int row) const
{
    auto & item = items[row];
    auto event = item.event;
    auto pItem = ResourceItem::get(event->owner());
    QString fileName = ObjectEvent::getFileName(event->eventType(), event->eventNumber());
    return QString("objects/%1/%2.gml").arg(pItem->name(), fileName);
}

void EventsModel::setModified(int row, bool modified)
{
    items[row].modified = modified;
    emit dataChanged(index(row), index(row), { Qt::DisplayRole });
}

bool EventsModel::isInherited(int row) const
{
    return items[row].inherited;
}

int EventsModel::findEvent(ObjectEvent::EventType eventType, int eventNumber)
{
    int i = 0;
    for (auto & eventItem : items)
    {
        if (eventItem.event->eventType() == eventType
            && eventItem.event->eventNumber() == eventNumber)
        {
            return i;
        }
        i++;
    }
    return -1;
}
