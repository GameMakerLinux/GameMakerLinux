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

#include "resourceitem.h"
#include "allresourceitems.h"
#include "utils/uuid.h"
#include <QMessageBox>
#include <QDebug>

ResourceItem::ResourceItem(ResourceType type)
    : m_type { type }
{
}

ResourceItem *ResourceItem::child(int index)
{
    if (index < children.size())
    {
        return children[index];
    }
    return nullptr;
}

void ResourceItem::initialize()
{
    // do nothing
}

QJsonObject ResourceItem::save()
{
    QMessageBox::warning(nullptr, "Unimplemented", QString("It's not possible to save this kind of resources: %1.").arg(Utils::resourceTypeToString(type())));
    return {};
}

QString ResourceItem::id() const
{
    return m_id;
}

void ResourceItem::setId(QString id)
{
    m_id = id;
}

QString ResourceItem::filename() const
{
    qCritical() << "Filename asked for object of type:" << Utils::resourceTypeToString(type());
    throw 42;
}

void ResourceItem::setName(QString name)
{
    m_name = name;
    emit nameChanged();
}

QPixmap ResourceItem::thumbnail(int width, int height) const
{
    Q_UNUSED(width)
    Q_UNUSED(height)
    return QPixmap();
}

ResourceItem * ResourceItem::create(ResourceType type, QString id)
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
    case ResourceType::BackgroundLayer:
        item = new BackgroundLayer;
        break;
    case ResourceType::Folder:
        item = new FolderResourceItem;
        break;
    case ResourceType::FolderLayer:
        item = new FolderLayer;
        break;
    case ResourceType::Font:
        item = new FontResourceItem;
        break;
    case ResourceType::HTML5Options:
        item = new HTML5OptionsResourceItem;
        break;
    case ResourceType::IncludedFile:
        item = new IncludedFileResourceItem;
        break;
    case ResourceType::iOSOptions:
        item = new iOSOptionsResourceItem;
        break;
    case ResourceType::InstanceLayer:
        item = new InstanceLayer;
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
    case ResourceType::Sound:
        item = new SoundResourceItem;
        break;
    case ResourceType::Sprite:
        item = new SpriteResourceItem;
        break;
    case ResourceType::tvOSOptions:
        item = new tvOSOptionsResourceItem;
        break;
    case ResourceType::TileLayer:
        item = new TileLayer;
        break;
    case ResourceType::TileSet:
        item = new TileSetResourceItem;
        break;
    case ResourceType::WindowsOptions:
        item = new WindowsOptionsResourceItem;
        break;
    case ResourceType::WindowsUAPOptions:
        item = new WindowsUAPOptionsResourceItem;
        break;
    default:
        item = new UnknownResourceItem;
    }

    item->setId(id);
    allResources[id] = item;

    return item;
}

void ResourceItem::remove(QString id)
{
    auto & children = allResources[id]->children;
    for (auto & child : children)
    {
        remove(child->id());
    }

    delete allResources[id];
    allResources.remove(id);
}

void ResourceItem::registerItem(QString id, ResourceItem * item)
{
    if (!Uuid::isNull(id))
    {
        allResources[id] = item;
    }
}

ResourceItem * ResourceItem::get(QString id)
{
    Q_ASSERT(!Uuid::isNull(id));
    if (allResources.contains(id))
        return allResources[id];
    return nullptr;
}

void ResourceItem::clear()
{
    qDeleteAll(allResources);
    allResources.clear();
}

ResourceItem * ResourceItem::findFolder(ResourceType filterType)
{
    auto folders = ResourceItem::findAll(ResourceType::Folder);
    for (auto & folderId : folders)
    {
        auto folderItem = ResourceItem::get<FolderResourceItem>(folderId);
        if (folderItem->filterType() == filterType && folderItem->isLocalised())
        {
            return folderItem;
        }
    }

    return nullptr;
}

QVector<QString> ResourceItem::findAll(ResourceType type)
{
    QVector<QString> items;
    QMapIterator<QString, ResourceItem*> it(allResources);
    while (it.hasNext())
    {
        it.next();

        if (it.value()->type() == type)
        {
            items.append(it.key());
        }
    }
    return items;
}

QMap<QString, ResourceItem *> ResourceItem::all()
{
    return allResources;
}

QString ResourceItem::generateName(ResourceType type)
{
    auto items = findAll(type);
    int id = 0;

    QString typeName;
    QString generatedName;

    switch (type)
    {
    case ResourceType::Folder:
        typeName = "folder";
        break;
    case ResourceType::Object:
        typeName = "object";
        break;
    case ResourceType::Script:
        typeName = "script";
        break;
    case ResourceType::Sprite:
        typeName = "sprite";
        break;
    default:
        Q_ASSERT(false);
    }

    while (true)
    {
        generatedName = QString("%1%2").arg(typeName).arg(id);
        auto b = std::find_if(items.begin(), items.end(), [&generatedName](QString id) {
            return allResources[id]->name() == generatedName;
        });

        id++;

        if (b == items.end())
        {
            break;
        }
    }

    return generatedName;
}
