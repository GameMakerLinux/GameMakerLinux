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

#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>
#include "resources/resourceitem.h"

namespace Ui {
class MainEditor;
}

class MainEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MainEditor(ResourceItem * resourceItem, QWidget *parent = 0);
    virtual ~MainEditor();

    bool isDirty() const { return dirty; }

protected:
    void setWidget(QWidget * widget);

    template <typename T>
    T * item()
    {
        return static_cast<T*>(resourceItem);
    }

protected slots:
    virtual void save() = 0;
    virtual void reset() = 0;
    void setDirty(bool b = true) { dirty = b; }

private:
    Ui::MainEditor * ui;
    ResourceItem * resourceItem;
    QLayout* targetLayout;
    bool dirty = false;
};

#endif // MAINEDITOR_H
