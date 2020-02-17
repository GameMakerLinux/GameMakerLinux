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

#ifndef OBJECTINSTANCE_H
#define OBJECTINSTANCE_H

#include "resources/resourceitem.h"
#include <QPoint>

class ObjectInstance : public ResourceItem
{
    Q_OBJECT

public:
    ObjectInstance();
    ObjectInstance(ObjectResourceItem * item);

    void load(QJsonObject object) override;
    QPoint position() const;
    void setPosition(int x, int y);
    ObjectResourceItem * object();

private:
    QPoint m_position;
    QString m_objId;
};

#endif // OBJECTINSTANCE_H
