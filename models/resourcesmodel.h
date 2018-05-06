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

#ifndef RESOURCESMODEL_H
#define RESOURCESMODEL_H

#include <QAbstractItemModel>
#include <memory>

#include "resources/resourceitem.h"


class ResourcesModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ResourcesModel(QObject *parent = nullptr);

    void clear();
    void fill(QMap<QString, ResourceItem *> resources);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool removeRows(int row, int count, const QModelIndex & parent) override;

    Qt::ItemFlags flags(const QModelIndex & index) const override;

    Qt::DropActions supportedDropActions() const override;
    Qt::DropActions supportedDragActions() const override;

    QStringList mimeTypes() const override;
    QMimeData * mimeData(const QModelIndexList & indexes) const override;

    bool canDropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) const override;
    bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) override;

private:
    ResourceItem * rootItem = nullptr;
};

#endif // RESOURCESMODEL_H
