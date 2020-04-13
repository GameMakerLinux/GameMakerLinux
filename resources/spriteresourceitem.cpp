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

#include "spriteresourceitem.h"
#include "dependencies/spriteframe.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QPixmap>
#include "gamesettings.h"

SpriteResourceItem::SpriteResourceItem()
    : ResourceItem { ResourceType::Sprite }
{
}

void SpriteResourceItem::load(QJsonObject object)
{
    setName(object["name"].toString());

    auto frames = object["frames"].toArray();
    for (auto frameJson : frames)
    {
        auto frame = new SpriteFrame;
        frame->load(frameJson.toObject());
        m_frames.push_back(frame);
    }
}

QPixmap SpriteResourceItem::thumbnail(int width, int height) const
{
    auto pix = pixmap();
    if (!pix.isNull())
    {
        pix = pix.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        pix = emptyThumbnail(width, height);
    }
    return pix;
}

QPixmap SpriteResourceItem::pixmap() const
{
    if (m_frames.size() > 0)
    {
        auto composite = m_frames[0]->compositeImage();
        QString path = QString("%1/sprites/%2/%3.png").arg(GameSettings::rootPath(), name(), composite->frameId());
        return QPixmap(path);
    }
    return QPixmap();
}


QString SpriteResourceItem::filename() const
{
    return QString("sprites/%1/%1.yy").arg(name());
}
