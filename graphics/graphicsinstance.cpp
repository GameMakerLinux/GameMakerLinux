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

#include "graphicsinstance.h"
#include "resources/dependencies/objectinstance.h"
#include <QIcon>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

GraphicsInstance::GraphicsInstance(ObjectInstance * instance)
    : QGraphicsPixmapItem { QIcon::fromTheme("help-about").pixmap(16, 16) }
    , m_objectInstance { instance }
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

    setPos(m_objectInstance->position());
    setToolTip(m_objectInstance->name());
}

ObjectInstance * GraphicsInstance::objectInstance() const
{
    return m_objectInstance;
}


void GraphicsInstance::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
    event->accept();

    QMenu menu;
    menu.addAction("Edit instance", [this]() {
        emit openInstance(this->objectInstance());
    });
    menu.addAction("Edit object", [this]() {
        emit openObject(this->objectInstance()->object());
    });
    menu.exec(event->screenPos());
}

QVariant GraphicsInstance::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant & value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged)
    {
        auto p = value.toPointF();
        m_objectInstance->setPosition(p);
    }

    return QGraphicsPixmapItem::itemChange(change, value);
}
