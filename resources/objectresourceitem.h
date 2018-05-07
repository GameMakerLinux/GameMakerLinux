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

    void load(QJsonObject object) override;
    QJsonObject save() override;
    QString filename() const override;

    int eventsCount() const;
    ObjectEvent * getEvent(int id) const;

    ObjectResourceItem * parentObject() const;
    void setParentObject(ObjectResourceItem * object);

    SpriteResourceItem * sprite() const;
    void setSprite(SpriteResourceItem * sprite);

    SpriteResourceItem * maskSprite() const;
    void setMaskSprite(SpriteResourceItem * sprite);

private:
    QVector<ObjectEvent*> eventsList;
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

    // Used on save in case the object name is changed
    QString m_oldName;
};

#endif // OBJECTRESOURCEITEM_H
