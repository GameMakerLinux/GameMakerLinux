#include "eventsmodel.h"
#include "resources/objectresourceitem.h"
#include "gamesettings.h"
#include "resources/dependencies/objectevent.h"

EventsModel::EventsModel(QObject *parent)
    : QAbstractListModel(parent)
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
        return ObjectEvent::getName(event->type(), event->number()) + (item.modified ? "*" : "");
    }

    return QVariant();
}

QString EventsModel::getFilename(int row) const
{
    auto & item = items[row];
    auto event = item.event;
    auto pItem = ResourceItem::get(event->owner());
    QString fileName = ObjectEvent::getFileName(event->type(), event->number());
    return QString("%1/objects/%2/%3.gml").arg(GameSettings::rootPath(), pItem->name(), fileName);
}

void EventsModel::setModified(int row, bool modified)
{
    items[row].modified = modified;
    emit dataChanged(index(row), index(row), { Qt::DisplayRole });
}
