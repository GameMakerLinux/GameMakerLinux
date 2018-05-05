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

#ifndef GRAPHICSINSTANCE_H
#define GRAPHICSINSTANCE_H

#include <QGraphicsPixmapItem>

class ObjectInstance;
class GraphicsInstance : public QGraphicsPixmapItem
{
public:
    GraphicsInstance(ObjectInstance * instance);

    ObjectInstance * objectInstance() const;

private:
    ObjectInstance * m_objectInstance = nullptr;
};

#endif // GRAPHICSINSTANCE_H
