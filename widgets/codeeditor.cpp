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

#include "codeeditor.h"
#include <QVBoxLayout>
#include "utils/gmlhighlighter.h"
#include <QDebug>

CodeEditor::CodeEditor(QWidget *parent)
    : QWidget { parent }
{
    textEdit = new Qutepart::Qutepart;
    connect(textEdit, &Qutepart::Qutepart::textChanged, this, &CodeEditor::textChanged);

    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(textEdit);
}

void CodeEditor::setCode(QString code)
{
    auto blocked = textEdit->blockSignals(true);
    textEdit->setPlainText(code);
    textEdit->blockSignals(blocked);
}

QString CodeEditor::getCode() const
{
    return textEdit->toPlainText();
}

void CodeEditor::setReadOnly(bool ro)
{
    textEdit->setReadOnly(ro);
}
