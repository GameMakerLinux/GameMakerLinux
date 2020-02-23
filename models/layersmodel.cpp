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

#include "layersmodel.h"
#include "resources/dependencies/instancelayer.h"
#include "resources/dependencies/folderlayer.h"
#include "resources/roomresourceitem.h"

LayersModel::LayersModel(QObject * parent)
    : QAbstractItemModel { parent }
{
}

void LayersModel::load(RoomResourceItem * item)
{
    clear();

    rootItem.reset(new LayerItem);
    addLayersToParent(rootItem.get(), item->rootLayers());
}

int LayersModel::rowCount(const QModelIndex & parent) const
{
    if (!parent.isValid())
    {
        if (rootItem == nullptr) return 0;
        return rootItem->children.size();
    }

    auto ptr = static_cast<LayerItem*>(parent.internalPointer());
    return ptr->children.size();
}

QVariant LayersModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = static_cast<LayerItem*>(index.internalPointer());
    switch (role)
    {
    case Qt::DisplayRole:
        return item->layer->name();
    case Qt::CheckStateRole:
        return item->visible;
    }

    return QVariant();
}

bool LayersModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid())
    {
        auto item = static_cast<LayerItem*>(index.internalPointer());
        switch (role)
        {
        case Qt::CheckStateRole:
            setCheckedState(item, value.value<Qt::CheckState>());
            auto topLeft = LayersModel::index(0, 0, QModelIndex());
            auto bottomRight = LayersModel::index(rootItem->children.count() - 1, 0, QModelIndex());
            emit dataChanged(topLeft, bottomRight, { Qt::CheckStateRole });
            return true;
        }
    }

    return false;
}

void LayersModel::clear()
{
    beginResetModel();
    rootItem.reset();
    endResetModel();
}

void LayersModel::setCheckedState(LayerItem * item, Qt::CheckState state)
{
    item->visible = state;
    visibilityChanged(item->layer, state == Qt::Checked);

    for (auto & c : item->children)
    {
        setCheckedState(c, state);
    }
}

void LayersModel::addLayersToParent(LayerItem * parentItem, QVector<RoomLayer *> layers)
{
    for (auto & layer : layers)
    {
        auto item = new LayerItem;
        item->layer = layer;

        parentItem->add(item);

        if (layer->type() == RoomLayer::Type::Folder)
        {
            auto folderLayer = qobject_cast<FolderLayer*>(layer);
            addLayersToParent(item, folderLayer->subLayers());
        }
    }
}

Qt::ItemFlags LayersModel::flags(const QModelIndex & index) const
{
    auto f = QAbstractItemModel::flags(index);
    return f | Qt::ItemIsUserCheckable;
}


QModelIndex LayersModel::index(int row, int column, const QModelIndex & parent) const
{
    LayerItem * ptr = nullptr;
    if (!parent.isValid())
        ptr = rootItem.get();
    else
        ptr = static_cast<LayerItem*>(parent.internalPointer());
    auto childPtr = ptr->child(row);
    return createIndex(row, column, childPtr);
}

QModelIndex LayersModel::parent(const QModelIndex & child) const
{
    auto ptr = static_cast<LayerItem*>(child.internalPointer());
    auto parentPtr = ptr->parent;
    if (parentPtr == rootItem.get())
        return QModelIndex();
    return createIndex(parentPtr->children.indexOf(ptr), 0, parentPtr);
}

int LayersModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return 1;
}
