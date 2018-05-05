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

#ifndef OBJECTRESOURCEITEM_H
#define OBJECTRESOURCEITEM_H

#include "resourceitem.h"
#include "utils/uuid.h"
#include "utils/utils.h"

class ObjectEvent;
class ObjectResourceItem : public ResourceItem
{
    Q_OBJECT

public:
    ObjectResourceItem();
    ~ObjectResourceItem();

    void load(QJsonObject object) override;

    int eventsCount() const;
    ObjectEvent * getEvent(int id) const;

    ObjectResourceItem * parentObject() const;
    SpriteResourceItem * sprite() const;
    SpriteResourceItem * maskSprite() const;

private:
    // mvc = "1.0"
    QVector<ObjectEvent*> eventsList; // replace by an object
    QString m_maskSpriteId;
    // TODO: overriddenProperties
    QString m_parentObjectId;
    bool m_persistent;
    double m_physicsAngularDamping;
    double m_physicsDensity;
    double m_physicsFriction;
    int m_physicsGroup;
    bool m_physicsKinematic;
    double m_physicsLinearDamping;
    bool m_physicsObject;
    double m_physicsRestitution;
    bool m_physicsSensor;
    int m_physicsShape;
    // TODO: physicsShapePoints
    bool m_physicsStartAwake;
    // TODO: properties
    bool m_solid;
    QString m_spriteId;
    bool m_visible;
};

#endif // OBJECTRESOURCEITEM_H
