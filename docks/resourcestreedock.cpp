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

#include "resourcestreedock.h"
#include "models/resourcesmodel.h"
#include "resources/allresourceitems.h"
#include "utils/utils.h"
#include <QVBoxLayout>
#include <QTreeView>
#include <QMenu>
#include <QDebug>

ResourcesTreeDock::ResourcesTreeDock()
{
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);

    resourcesTree = new QTreeView;
    resourcesTree->setDropIndicatorShown(true);
    resourcesTree->setDragDropMode(QAbstractItemView::InternalMove);
    resourcesTree->setFocusPolicy(Qt::NoFocus);
    resourcesTree->setContextMenuPolicy(Qt::CustomContextMenu);
    setWidget(resourcesTree);

    connect(resourcesTree, &QTreeView::customContextMenuRequested, this, &ResourcesTreeDock::onContextMenuRequested);
    connect(resourcesTree, &QTreeView::doubleClicked, this, &ResourcesTreeDock::onItemDoubleClicked);
}

void ResourcesTreeDock::setModel(ResourcesModel * model)
{
    resourcesTree->setModel(model);
}

void ResourcesTreeDock::onItemDoubleClicked(const QModelIndex & index)
{
    auto resourceItem = static_cast<ResourceItem*>(index.internalPointer());

    switch (resourceItem->type())
    {
    case ResourceType::AmazonFireOptions:
        emit openAmazonFireOptions(qobject_cast<AmazonFireOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::AndroidOptions:
        emit openAndroidOptions(qobject_cast<AndroidOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::Folder:
        // nothing to do
        break;
    case ResourceType::IncludedFile:
        emit openIncludedFile(qobject_cast<IncludedFileResourceItem*>(resourceItem));
        break;
    case ResourceType::iOSOptions:
        emit openiOsOptions(qobject_cast<iOSOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::LinuxOptions:
        emit openLinuxOptions(qobject_cast<LinuxOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::MacOptions:
        emit openMacOptions(qobject_cast<MacOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::MainOptions:
        emit openMainOptions(qobject_cast<MainOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::Object:
        emit openObject(qobject_cast<ObjectResourceItem*>(resourceItem));
        break;
    case ResourceType::Room:
        emit openRoom(qobject_cast<RoomResourceItem*>(resourceItem));
        break;
    case ResourceType::Script:
        emit openScript(qobject_cast<ScriptResourceItem*>(resourceItem));
        break;
    case ResourceType::Sprite:
        emit openSprite(qobject_cast<SpriteResourceItem*>(resourceItem));
        break;
    case ResourceType::WindowsOptions:
        emit openWindowsOptions(qobject_cast<WindowsOptionsResourceItem*>(resourceItem));
        break;
    default:
        qCritical() << "Unimplemented element:" << Utils::resourceTypeToString(resourceItem->type());
    }
}

void ResourcesTreeDock::onContextMenuRequested(const QPoint & pos)
{
    auto modelIndex = resourcesTree->indexAt(pos);
    if (modelIndex.isValid())
    {
        QMenu contextMenu(this);

        auto item = static_cast<ResourceItem*>(modelIndex.internalPointer());
        switch (item->type())
        {
        case ResourceType::AmazonFireOptions:
            break;
        case ResourceType::AndroidOptions:
            break;
        case ResourceType::BackgroundLayer:
            break;
        case ResourceType::Config:
            break;
        case ResourceType::Event:
            break;
        case ResourceType::Extension:
            break;
        case ResourceType::Folder:
            addItemAction(&contextMenu, static_cast<FolderResourceItem*>(item));
            break;
        case ResourceType::Font:
            break;
        case ResourceType::ImageLayer:
            break;
        case ResourceType::IncludedFile:
            break;
        case ResourceType::InstanceLayer:
            break;
        case ResourceType::iOSOptions:
            break;
        case ResourceType::LinuxOptions:
            break;
        case ResourceType::Notes:
            break;
        case ResourceType::MacOptions:
            break;
        case ResourceType::MainOptions:
            break;
        case ResourceType::Object:
            break;
        case ResourceType::Options:
            break;
        case ResourceType::ObjectInstance:
            break;
        case ResourceType::Path:
            break;
        case ResourceType::Project:
            break;
        case ResourceType::Room:
            break;
        case ResourceType::Root:
            break;
        case ResourceType::RoomSettings:
            break;
        case ResourceType::Sound:
            break;
        case ResourceType::Script:
            break;
        case ResourceType::Shader:
            break;
        case ResourceType::Sprite:
            break;
        case ResourceType::SpriteFrame:
            break;
        case ResourceType::SpriteImage:
            break;
        case ResourceType::TileSet:
            break;
        case ResourceType::Timeline:
            break;
        case ResourceType::Unknown:
            break;
        case ResourceType::WindowsOptions:
            break;
        }

        if (contextMenu.actions().count())
            contextMenu.exec(QCursor::pos());
    }
}

void ResourcesTreeDock::addItemAction(QMenu * menu, FolderResourceItem * folder)
{
    switch (folder->filterType())
    {
    case ResourceType::Sprite:
        menu->addAction(QString("Add a '%1'").arg(folder->name()));
        break;
    default:
        ;
    }
}
