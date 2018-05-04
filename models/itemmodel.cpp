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

#include "itemmodel.h"
#include "resources/resourceitem.h"

ItemModel::ItemModel(ResourceItem * item, QObject *parent)
    : QAbstractItemModel(parent)
    , rootItem(item)
{
}

QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent) const
{
    ResourceItem* ptr = nullptr;
    if (!parent.isValid())
        ptr = rootItem;
    else
        ptr = static_cast<ResourceItem*>(parent.internalPointer());
    if (row == 0) return createIndex(row, column, ptr);
    auto childPtr = ptr->child(row - 1);
    return createIndex(row, column, childPtr);
}

QModelIndex ItemModel::parent(const QModelIndex &index) const
{
    if (index.row() == 0)
    {
        auto ptr = static_cast<ResourceItem*>(index.internalPointer());
        if (ptr == rootItem)
            return QModelIndex();
        return createIndex(0, 0, ptr);
    }
    else
    {
        auto ptr = static_cast<ResourceItem*>(index.internalPointer());
        auto parentPtr = ptr->parentItem;
        if (parentPtr == rootItem)
            return QModelIndex();
        return createIndex(parentPtr->children.indexOf(ptr), 0, parentPtr);
    }
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        if (rootItem == nullptr) return 0;
        return rootItem->children.size() + 1;
    }

    auto ptr = static_cast<ResourceItem*>(parent.internalPointer());
    return ptr->children.size() + 1;
}

int ItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.row() == 0)
        {
            if (index.parent().isValid())
                return "...";
            else
                return "<Nothing>";
        }
        else
        {
            auto ptr = static_cast<ResourceItem*>(index.internalPointer());
            return ptr->name();
        }
    }

    return QVariant();
}
