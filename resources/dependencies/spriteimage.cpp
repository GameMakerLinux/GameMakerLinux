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

#include "spriteimage.h"
#include <QPixmap>

SpriteImage::SpriteImage()
    : ResourceItem { ResourceType::SpriteImage }
{
}

void SpriteImage::load(QJsonObject object)
{
    id = object["id"].toString();
    ResourceItem::registerItem(id, this);

    setName("SpriteImage");

    m_frameId = object["FrameId"].toString();
    m_layerId = object["LayerId"].toString();
}

QString SpriteImage::frameId() const
{
    return m_frameId;
}

QString SpriteImage::layerId() const
{
    return m_layerId;
}
