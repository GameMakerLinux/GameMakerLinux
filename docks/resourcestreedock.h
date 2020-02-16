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

#ifndef RESOURCESTREEDOCK_H
#define RESOURCESTREEDOCK_H

#include <QDockWidget>

#include "resources/resourceitem.h"

class QMenu;
class QTreeView;
class ResourcesModel;
class ResourcesTreeDock : public QDockWidget
{
    Q_OBJECT

public:
    ResourcesTreeDock();

    void setModel(ResourcesModel* model);

signals:
    void openSprite(SpriteResourceItem* item);
    void openRoom(RoomResourceItem* item);
    void openScript(ScriptResourceItem* item);
    void openAndroidOptions(AndroidOptionsResourceItem* item);
    void openAmazonFireOptions(AmazonFireOptionsResourceItem* item);
    void openWindowsOptions(WindowsOptionsResourceItem* item);
    void openLinuxOptions(LinuxOptionsResourceItem* item);
    void openMacOptions(MacOptionsResourceItem* item);
    void openiOsOptions(iOSOptionsResourceItem* item);
    void openIncludedFile(IncludedFileResourceItem* item);
    void openMainOptions(MainOptionsResourceItem* item);
    void openObject(ObjectResourceItem* item);

    void itemRemoved(QString id);

private slots:
    void onItemDoubleClicked(const QModelIndex & index);
    void onContextMenuRequested(const QPoint & pos);

private:
    QTreeView * resourcesTree;
    ResourcesModel * resModel;

    // context menu handling
    void addItemAction(QMenu * menu, ResourceType type, QModelIndex index);
    void deleteItemAction(QMenu * menu, ResourceType type, QModelIndex index);
};

#endif // RESOURCESTREEDOCK_H
