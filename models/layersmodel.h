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

#include <QAbstractListModel>

class RoomLayer;
struct LayerItem
{
    RoomLayer * layer;
    Qt::CheckState visible = Qt::Checked;
    bool locked = false; // unused
};

class LayersModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LayersModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;

    bool setData(const QModelIndex & index, const QVariant & value, int role) override;

    void addLayer(RoomLayer * layer);
    RoomLayer * layer(int row) const;

    void clear();

signals:
    void visibilityChanged(QString id, bool visible);

private:
    QVector<LayerItem> items;
};

#endif // LAYERSMODEL_H
