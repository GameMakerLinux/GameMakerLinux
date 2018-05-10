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

#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include "roomlayer.h"
#include <QColor>

class BackgroundLayer : public RoomLayer
{
    Q_OBJECT

public:
    BackgroundLayer();

    void load(QJsonObject object);

    SpriteResourceItem * sprite() const;
    QColor colour() const;

private:
    QString m_spriteId;
    QColor m_colour = Qt::black;
};

#endif // BACKGROUNDLAYER_H
