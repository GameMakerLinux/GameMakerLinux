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

#include "resourceitem.h"
#include "allresourceitems.h"

ResourceItem::ResourceItem(ResourceType type)
    : type { type }
{
}

ResourceItem::~ResourceItem()
{
    qDeleteAll(children);
}

ResourceItem *ResourceItem::child(int index)
{
    if (index < children.size())
    {
        return children[index];
    }
    return nullptr;
}

void ResourceItem::setName(QString name)
{
    m_name = name;
    emit nameChanged();
}

ResourceItem *ResourceItem::create(ResourceType type)
{
    switch (type)
    {
    case ResourceType::AmazonFireOptions:
        return new AmazonFireOptionsResourceItem;
    case ResourceType::AndroidOptions:
        return new AndroidOptionsResourceItem;
    case ResourceType::Folder:
        return new FolderResourceItem;
    case ResourceType::IncludedFile:
        return new IncludedFileResourceItem;
    case ResourceType::iOSOptions:
        return new iOSOptionsResourceItem;
    case ResourceType::LinuxOptions:
        return new LinuxOptionsResourceItem;
    case ResourceType::MacOptions:
        return new MacOptionsResourceItem;
    case ResourceType::MainOptions:
        return new MainOptionsResourceItem;
    case ResourceType::Object:
        return new ObjectResourceItem;
    case ResourceType::Room:
        return new RoomResourceItem;
    case ResourceType::Script:
        return new ScriptResourceItem;
    case ResourceType::Sprite:
        return new SpriteResourceItem;
    case ResourceType::WindowsOptions:
        return new WindowsOptionsResourceItem;
    default:
        return new UnknownResourceItem;
    }
}
