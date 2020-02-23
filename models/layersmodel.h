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

#ifndef LAYERSMODEL_H
#define LAYERSMODEL_H

#include <QAbstractItemModel>

class RoomLayer;
struct LayerItem
{
    ~LayerItem()
    {
        qDeleteAll(children);
    }

    RoomLayer * layer = nullptr;
    LayerItem * parent = nullptr;
    Qt::CheckState visible = Qt::Checked;
    bool locked = false; // unused
    QVector<LayerItem*> children;

    void add(LayerItem * item)
    {
        item->parent = this;
        children.push_back(item);
    }

    LayerItem * child(int row)
    {
        return children.at(row);
    }
};

class RoomResourceItem;
class LayersModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit LayersModel(QObject *parent = nullptr);

    void load(RoomResourceItem * item);

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;
    QModelIndex index(int row, int column, const QModelIndex & parent) const override;
    QModelIndex parent(const QModelIndex & child) const override;
    int columnCount(const QModelIndex & parent) const override;

    bool setData(const QModelIndex & index, const QVariant & value, int role) override;

    void clear();

signals:
    void visibilityChanged(RoomLayer * layer, bool visible);

private:
    void setCheckedState(LayerItem * item, Qt::CheckState state);
    void addLayersToParent(LayerItem * parentItem, QVector<RoomLayer*> layers);

    QScopedPointer<LayerItem> rootItem;
};

#endif // LAYERSMODEL_H
