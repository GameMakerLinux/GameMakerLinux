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
    QPixmap thumbnail(int width, int height) const override;

    int eventsCount() const;
    ObjectEvent * getEvent(int id) const;
    void addEvent(ObjectEvent * event);
    void clearEvents();

    ObjectResourceItem * parentObject() const;
    void setParentObject(ObjectResourceItem * object);

    SpriteResourceItem * sprite() const;
    void setSprite(SpriteResourceItem * sprite);

    SpriteResourceItem * maskSprite() const;
    void setMaskSprite(SpriteResourceItem * sprite);

    bool isKinematic() const;
    void setKinematic(bool b);

    bool isPersistent() const;
    void setPersistent(bool b);

    bool usesPhysics() const;
    void setPhysics(bool b);

    bool startsAwake() const;
    void startAwake(bool b);

    bool isVisible() const;
    void setVisible(bool b);

    bool isSolid() const;
    void setSolid(bool b);

    bool isSensor() const;
    void setSensor(bool b);

#define PHYSICS_GETTER_SETTER(name, type) \
    type get ## name () const { return m_physics ## name ; } \
    void set ## name (type v) { m_physics ## name = v; }

    PHYSICS_GETTER_SETTER(Density, double)
    PHYSICS_GETTER_SETTER(Restitution, double)
    PHYSICS_GETTER_SETTER(Group, int)
    PHYSICS_GETTER_SETTER(LinearDamping, double)
    PHYSICS_GETTER_SETTER(AngularDamping, double)
    PHYSICS_GETTER_SETTER(Friction, double)

#undef PHYSICS_GETTER_SETTER

private:
    QVector<ObjectEvent*> eventsList;
    QString m_maskSpriteId;
    // TODO: overriddenProperties
    QString m_parentObjectId;
    bool m_persistent = false;
    double m_physicsAngularDamping = 0;
    double m_physicsDensity = 0;
    double m_physicsFriction = 0;
    int m_physicsGroup = 0;
    bool m_physicsKinematic = false;
    double m_physicsLinearDamping = 0;
    bool m_physicsObject = false;
    double m_physicsRestitution = 0;
    bool m_physicsSensor = false;
    int m_physicsShape = 0;
    // TODO: physicsShapePoints
    bool m_physicsStartAwake = false;
    // TODO: properties
    bool m_solid = false;
    QString m_spriteId;
    bool m_visible = true;
};

#endif // OBJECTRESOURCEITEM_H
