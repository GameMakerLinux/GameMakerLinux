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

#include "graphicsinstance.h"
#include "resources/dependencies/objectinstance.h"
#include <QIcon>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QPainter>

GraphicsInstance::GraphicsInstance(ObjectInstance * instance)
    : QGraphicsPixmapItem { QIcon::fromTheme("help-about").pixmap(16, 16) }
    , m_objectInstance { instance }
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    setPos(m_objectInstance->position());
    setToolTip(m_objectInstance->name());
}

ObjectInstance * GraphicsInstance::objectInstance() const
{
    return m_objectInstance;
}
