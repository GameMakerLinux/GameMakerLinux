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

#ifndef ROOMLAYER_H
#define ROOMLAYER_H

#include "resources/resourceitem.h"

class RoomLayer : public ResourceItem
{
    Q_OBJECT

public:
    enum class Type {
        Instances,
        Background,
        Unknown
    };

    RoomLayer(ResourceType type);
    ~RoomLayer() = default;

    void load(QJsonObject object);
    Type type() const;

    int depth() const;

protected:
    void setDepth(int d);

private:
    int m_depth = 0;
    Type m_type = Type::Unknown;
};

#endif // ROOMLAYER_H
