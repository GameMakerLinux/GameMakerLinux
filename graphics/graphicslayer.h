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

#ifndef GRAPHICSLAYER_H
#define GRAPHICSLAYER_H

#include <QGraphicsItem>

class ObjectInstance;
class GraphicsLayer : public QGraphicsItem
{
public:
    GraphicsLayer();

    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;

    void selectItem(ObjectInstance * instance);
    void setElementVisible(ObjectInstance * instance, bool visible);
    bool isElementVisible(ObjectInstance * instance) const;

    void setCurrent(bool b);
};

#endif // GRAPHICSLAYER_H
