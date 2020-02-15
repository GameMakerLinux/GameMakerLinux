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

LayersModel::LayersModel(QObject *parent)
    : QAbstractListModel { parent }
{
}

int LayersModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return items.size();
}

QVariant LayersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto & item = items[index.row()];
    switch (role)
    {
    case Qt::DisplayRole:
        return item.layer->name();
    case Qt::CheckStateRole:
        return item.visible;
    }

    return QVariant();
}

bool LayersModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid())
    {
        switch (role)
        {
        case Qt::CheckStateRole:
            items[index.row()].visible = value.value<Qt::CheckState>();

            visibilityChanged(items[index.row()].layer->id(), value.value<Qt::CheckState>() == Qt::Checked);
            return true;
        }
    }

    return false;
}

void LayersModel::addLayer(RoomLayer * layer)
{
    beginInsertRows(QModelIndex(), items.size(), items.size());
    items.append({ layer });
    endInsertRows();
}

RoomLayer * LayersModel::layer(int row) const
{
    return items[row].layer;
}

void LayersModel::clear()
{
    beginResetModel();
    items.clear();
    endResetModel();
}

Qt::ItemFlags LayersModel::flags(const QModelIndex & index) const
{
    auto f = QAbstractListModel::flags(index);
    return f | Qt::ItemIsUserCheckable;
}
