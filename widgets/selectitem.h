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

#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QDialog>
#include "models/itemmodel.h"

class ResourceItem;
class QListView;
class SelectItem : public QDialog
{
public:
    SelectItem(ResourceItem * rootElement, ResourceItem * excludedElement = nullptr);

    ResourceItem * choice() const;

private slots:
    void itemClicked(QModelIndex index);
    void itemDoubleClicked(QModelIndex index);

private:
    ItemModel model;
    QListView * listView = nullptr;
    ResourceItem * selectedItem = nullptr;
};

#endif // SELECTITEM_H
