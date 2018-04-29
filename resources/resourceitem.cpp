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
    : m_type { type }
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

void ResourceItem::save()
{
}

void ResourceItem::setName(QString name)
{
    m_name = name;
    emit nameChanged();
}

ResourceItem *ResourceItem::create(ResourceType type, QString id)
{
    ResourceItem * item = nullptr;

    switch (type)
    {
    case ResourceType::AmazonFireOptions:
        item = new AmazonFireOptionsResourceItem;
        break;
    case ResourceType::AndroidOptions:
        item = new AndroidOptionsResourceItem;
        break;
    case ResourceType::Folder:
        item = new FolderResourceItem;
        break;
    case ResourceType::IncludedFile:
        item = new IncludedFileResourceItem;
        break;
    case ResourceType::iOSOptions:
        item = new iOSOptionsResourceItem;
        break;
    case ResourceType::LinuxOptions:
        item = new LinuxOptionsResourceItem;
        break;
    case ResourceType::MacOptions:
        item = new MacOptionsResourceItem;
        break;
    case ResourceType::MainOptions:
        item = new MainOptionsResourceItem;
        break;
    case ResourceType::Object:
        item = new ObjectResourceItem;
        break;
    case ResourceType::Room:
        item = new RoomResourceItem;
        break;
    case ResourceType::Script:
        item = new ScriptResourceItem;
        break;
    case ResourceType::Sprite:
        item = new SpriteResourceItem;
        break;
    case ResourceType::WindowsOptions:
        item = new WindowsOptionsResourceItem;
        break;
    default:
        item = new UnknownResourceItem;
    }

    item->id = id;
    allResources[id] = item;

    return item;
}

ResourceItem *ResourceItem::get(QString id)
{
    return allResources[id];
}
