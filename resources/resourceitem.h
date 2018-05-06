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
    AmazonFireOptions,
    AndroidOptions,
    BackgroundLayer,
    Config,
    Event,
    Extension,
    Folder,
    Font,
    ImageLayer,
    IncludedFile,
    InstanceLayer,
    iOSOptions,
    LinuxOptions,
    MacOptions,
    MainOptions,
    Notes,
    Object,
    ObjectInstance,
    Options,
    Path,
    Room,
    RoomSettings,
    Root,
    Script,
    Shader,
    Sound,
    Sprite,
    SpriteFrame,
    SpriteImage,
    TileSet,
    Timeline,
    WindowsOptions,
    Unknown
};

class ResourceItem : public QObject
{
    Q_OBJECT

public:
    ResourceItem* child(int index);
    virtual void load(QJsonObject object) = 0;
    virtual void save();

    QString name() const { return m_name; }
    void setName(QString name);
    virtual QPixmap thumbnail() const;

    ResourceType type() const { return m_type; }

    QString id;
    QString filename;

    QVector<ResourceItem*> children;
    ResourceItem* parentItem = nullptr;

    static ResourceItem* create(ResourceType type, QString id);
    static void registerItem(QString id, ResourceItem * item);
    static ResourceItem* get(QString id);
    template <typename T>
    static T* get(QString id)
    {
        return qobject_cast<T*>(ResourceItem::get(id));
    }
    static void clear();

    static ResourceItem * findFolder(ResourceType filterType);
    static QVector<QString> findAll(ResourceType type);

signals:
    void nameChanged();

protected:
    ResourceItem(ResourceType type);

private:
    QString m_name;
    ResourceType m_type;

    static QMap<QString, ResourceItem*> allResources;
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
class SoundResourceItem;
class FontResourceItem;
class RoomLayer;
class BackgroundLayer;
class InstanceLayer;
class ObjectInstance;
class RoomSettings;

#endif // RESOURCEITEM_H
