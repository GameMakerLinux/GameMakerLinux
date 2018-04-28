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

#include "maineditor.h"
#include "ui_maineditor.h"
#include <QPushButton>

MainEditor::MainEditor(ResourceItem * resourceItem, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainEditor)
    , resourceItem(resourceItem)
{
    ui->setupUi(this);

    targetLayout = new QVBoxLayout(ui->editorWidget);
    targetLayout->setMargin(0);

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &MainEditor::save);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked, this, &MainEditor::reset);
}

MainEditor::~MainEditor()
{
    delete ui;
}

void MainEditor::setWidget(QWidget * widget)
{
    targetLayout->addWidget(widget);
}
