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

#include "scripteditor.h"
#include "widgets/codeeditor.h"
#include "resources/scriptresourceitem.h"
#include <QFile>
#include "gamesettings.h"
#include <QDebug>

ScriptEditor::ScriptEditor(ScriptResourceItem * item)
    : MainEditor { item }
{
    codeEditor = new CodeEditor;
    setWidget(codeEditor);

    codeEditor->setCode(item->code());
    connect(codeEditor, &CodeEditor::textChanged, [this, item]() {
        item->setCode(codeEditor->getCode());
    });
}

void ScriptEditor::save()
{
    auto name = item<ScriptResourceItem>()->name();

    QString path = QString("%1/%2").arg(GameSettings::rootPath(), item<ScriptResourceItem>()->scriptFilename());
    QFile f(path);
    if (!f.open(QFile::WriteOnly))
    {
        qCritical() << "Can't open file" << path << "in write only mode";
        return;
    }

    f.write(codeEditor->getCode().toLocal8Bit());
    f.close();
}
