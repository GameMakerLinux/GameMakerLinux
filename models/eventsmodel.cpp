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

EventsModel::EventsModel(QObject *parent)
    : QAbstractListModel { parent }
{
}

void EventsModel::addEvent(ObjectEvent * event)
{
    beginInsertRows(QModelIndex(), items.size(), items.size());
    items.push_back({ event });
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
