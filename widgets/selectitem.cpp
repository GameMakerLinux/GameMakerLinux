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

#include "selectitem.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListView>
#include "models/itemmodel.h"
#include "resources/resourceitem.h"
#include <QDebug>

SelectItem::SelectItem(ResourceItem * rootElement)
{
    setWindowTitle("Select parent");

    listView = new QListView;
    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(listView);
    layout->addWidget(buttons);

    model = new ItemModel(rootElement);
    listView->setModel(model);

    connect(buttons, &QDialogButtonBox::accepted, this, &SelectItem::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &SelectItem::reject);

    connect(listView, &QListView::doubleClicked, this, &SelectItem::itemClicked);
}

ResourceItem *SelectItem::choice() const
{
    return selectedItem;
}

void SelectItem::itemClicked(QModelIndex index)
{
    // first item is always "go back" or "no sprites" if at the top
    if (index.row() == 0)
    {
        if (index.parent().isValid())
        {
            listView->setRootIndex(index.parent());
        }
        else
        {
            selectedItem = nullptr;
            accept();
        }
        return;
    }

    auto pItem = static_cast<ResourceItem*>(index.internalPointer());
    if (pItem->type() == ResourceType::Folder)
    {
        listView->setRootIndex(index);
    }
    else
    {
        selectedItem = pItem;
        accept();
    }
}
