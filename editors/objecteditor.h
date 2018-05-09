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

#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H

#include "maineditor.h"
#include "resources/objectresourceitem.h"
#include "ui_objecteditor.h"
#include "models/eventsmodel.h"
#include "widgets/formedit.h"

class ObjectEditor : public MainEditor
{
    Q_OBJECT

public:
    ObjectEditor(ObjectResourceItem* item);

protected slots:
    void save() override;
    void reset() override;
    void setDirty(bool dirty = true) override;

private slots:
    void onEventsAdded(const QModelIndex &parent, int first, int last);
    void onEventsRemoved(const QModelIndex &parent, int first, int last);
    void onEventsCleared();
    void chooseParent();
    void chooseMask();
    void chooseSprite();

private:
    Ui::ObjectEditor * ui;
    FormEdit * m_density;
    FormEdit * m_restitution;
    FormEdit * m_collisionGroup;
    FormEdit * m_linearDamping;
    FormEdit * m_angularDamping;
    FormEdit * m_friction;

    EventsModel eventsModel;
    ObjectResourceItem * m_parentObject = nullptr;
    SpriteResourceItem * m_sprite = nullptr;
    SpriteResourceItem * m_maskSprite = nullptr;
};

#endif // OBJECTEDITOR_H
