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

#include "objectsmodel.h"
#include "resources/dependencies/objectinstance.h"

ObjectsModel::ObjectsModel(QObject *parent)
    : QAbstractListModel { parent }
{
}

int ObjectsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return items.size();
}

QVariant ObjectsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto & item = items[index.row()];
    switch (role)
    {
    case Qt::DisplayRole:
        return item.object->name();
    case Qt::CheckStateRole:
        return item.visible;
    }

    return QVariant();
}

Qt::ItemFlags ObjectsModel::flags(const QModelIndex & index) const
{
    auto f = QAbstractListModel::flags(index);
    return f | Qt::ItemIsUserCheckable;
}

bool ObjectsModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid())
    {
        switch (role)
        {
        case Qt::CheckStateRole:
            items[index.row()].visible = value.value<Qt::CheckState>();

            visibilityChanged(items[index.row()].object->id(), value.value<Qt::CheckState>() == Qt::Checked);
            return true;
        }
    }

    return false;
}

void ObjectsModel::addObject(ObjectInstance * object)
{
    beginInsertRows(QModelIndex(), items.size(), items.size());
    items.append({ object });
    endInsertRows();
}

int ObjectsModel::rowOf(ObjectInstance * object) const
{
    int i = 0;
    for (auto & item : items)
    {
        if (item.object == object)
        {
            return i;
        }
        i++;
    }
    return -1;
}

QModelIndex ObjectsModel::indexOf(ObjectInstance * object) const
{
    auto row = rowOf(object);
    if (row != -1)
        return index(row);
    return QModelIndex();
}

ObjectInstance *ObjectsModel::objectInstance(int row) const
{
    if (row < items.size())
        return items[row].object;
    return nullptr;
}

void ObjectsModel::clear()
{
    beginResetModel();
    items.clear();
    endResetModel();
}
