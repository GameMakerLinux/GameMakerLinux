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
#include <QMap>

enum class ResourceType
{
    Folder,
    Object,
    Room,
    Sprite,
    Script,
    Font,
    Sound,
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
    virtual ~ResourceItem();

    ResourceItem* child(int index);
    virtual void load(QJsonObject object) = 0;
    virtual void save();

    QString name() const { return m_name; }
    void setName(QString name);

    ResourceType type() const { return m_type; }

    QString id;
    QString filename;

    QVector<ResourceItem*> children;
    ResourceItem* parentItem = nullptr;

    static ResourceItem* create(ResourceType type, QString id);
    static ResourceItem* get(QString id);

signals:
    void nameChanged();

protected:
    ResourceItem(ResourceType type);

private:
    QString m_name;
    ResourceType m_type;

    static inline QMap<QString, ResourceItem*> allResources;
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
