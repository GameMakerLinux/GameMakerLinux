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

#ifndef RESOURCEITEM_H
#define RESOURCEITEM_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QObject>

enum class ResourceType
{
    Folder,
    Object,
    Room,
    Sprite,
    Script,
    MainOptions,
    iOSOptions,
    IncludedFile,
    AmazonFireOptions,
    LinuxOptions,
    WindowsOptions,
    AndroidOptions,
    MacOptions,
    Unknown
};

class ResourceItem : public QObject
{
    Q_OBJECT

public:
    ResourceItem(ResourceType type);
    virtual ~ResourceItem();

    ResourceItem* child(int index);
    virtual void load(QJsonObject object) = 0;

    QString name() const { return m_name; }
    void setName(QString name);

    QString id;
    QString filename;
    ResourceType type;

    QVector<ResourceItem*> children;
    ResourceItem* parentItem = nullptr;

    static ResourceItem* create(ResourceType type);

signals:
    void nameChanged();

protected:
    ResourceItem();

private:
    QString m_name;
};

class SpriteResourceItem;
class UnknownResourceItem;
class FolderResourceItem;
class MainOptionsResourceItem;
class ScriptResourceItem;
class ObjectResourceItem;
class RoomResourceItem;
class AmazonFireOptionsResourceItem;
class AndroidOptionsResourceItem;
class IncludedFileResourceItem;
class iOSOptionsResourceItem;
class LinuxOptionsResourceItem;
class MacOptionsResourceItem;
class WindowsOptionsResourceItem;

#endif // RESOURCEITEM_H
