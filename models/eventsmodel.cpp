#include "eventsmodel.h"

EventsModel::EventsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void EventsModel::addEvent(QString name, QString filename)
{
    beginInsertRows(QModelIndex(), items.size(), items.size());
    items.push_back({ name, filename });
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
    switch (role)
    {
    case Qt::DisplayRole:
        return item.name + (item.modified ? "*" : "");
    }

    return QVariant();
}

QString EventsModel::getFilename(int row) const
{
    return items[row].filename;
}
