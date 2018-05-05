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

#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

#include "resources/resourceitem.h"
#include "spriteimage.h"

class SpriteFrame : public ResourceItem
{
public:
    SpriteFrame();
    ~SpriteFrame();

    void load(QJsonObject object) override;

    SpriteImage * compositeImage() const;

private:
    SpriteImage * m_compositeImage = nullptr;
};

#endif // SPRITEFRAME_H
