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

#include "objecteditor.h"

ObjectEditor::ObjectEditor(ObjectResourceItem* item)
    : MainEditor(item)
    , ui(new Ui::ObjectEditor)
{
    QTabWidget * tabWidget = new QTabWidget;
    ui->setupUi(tabWidget);
    setWidget(tabWidget);

    tabWidget->setCurrentIndex(0);

    connect(ui->nameLineEdit, &QLineEdit::textEdited, [this](QString) {
        this->setDirty();
    });

    // reset == load from item
    reset();
}

void ObjectEditor::save()
{
    auto name = ui->nameLineEdit->text();
    item<ObjectResourceItem>()->setName(name);
    emit nameChanged(name);

    setDirty(false);
}

void ObjectEditor::reset()
{
    auto pItem = item<ObjectResourceItem>();

    // GENERAL SETTINGS
    ui->nameLineEdit->setText(pItem->name());

    setDirty(false);
}
