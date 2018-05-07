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
#include <QVBoxLayout>
#include <QTreeView>
#include "models/resourcesmodel.h"
#include "resources/allresourceitems.h"
#include "utils/utils.h"
#include <QDebug>

ResourcesTreeDock::ResourcesTreeDock()
{
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);

    resourcesTree = new QTreeView;
    resourcesTree->setDropIndicatorShown(true);
    resourcesTree->setDragDropMode(QAbstractItemView::InternalMove);
    resourcesTree->setFocusPolicy(Qt::NoFocus);
    setWidget(resourcesTree);

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
        emit openAmazonFireOptions(static_cast<AmazonFireOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::AndroidOptions:
        emit openAndroidOptions(static_cast<AndroidOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::Folder:
        resourcesTree->setExpanded(index, resourcesTree->isExpanded(index));
        break;
    case ResourceType::IncludedFile:
        emit openIncludedFile(static_cast<IncludedFileResourceItem*>(resourceItem));
        break;
    case ResourceType::iOSOptions:
        emit openiOsOptions(static_cast<iOSOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::LinuxOptions:
        emit openLinuxOptions(static_cast<LinuxOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::MacOptions:
        emit openMacOptions(static_cast<MacOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::MainOptions:
        emit openMainOptions(static_cast<MainOptionsResourceItem*>(resourceItem));
        break;
    case ResourceType::Object:
        emit openObject(static_cast<ObjectResourceItem*>(resourceItem));
        break;
    case ResourceType::Room:
        emit openRoom(static_cast<RoomResourceItem*>(resourceItem));
        break;
    case ResourceType::Script:
        emit openScript(static_cast<ScriptResourceItem*>(resourceItem));
        break;
    case ResourceType::Sprite:
        emit openSprite(static_cast<SpriteResourceItem*>(resourceItem));
        break;
    case ResourceType::WindowsOptions:
        emit openWindowsOptions(static_cast<WindowsOptionsResourceItem*>(resourceItem));
        break;
    default:
        qCritical() << "Unimplemented element:" << Utils::resourceTypeToString(resourceItem->type());
    }
}
