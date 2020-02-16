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

#include "resourcesmodel.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include "utils/utils.h"
#include "resources/folderresourceitem.h"
#include <QMimeData>
#include <QPixmap>
#include <QFont>

static int QT_FIX_DND = -1;

ResourcesModel::ResourcesModel(QObject *parent)
    : QAbstractItemModel { parent }
{
}

void ResourcesModel::clear()
{
    beginResetModel();
    rootItem = nullptr;
    endResetModel();
}

void ResourcesModel::fill(QMap<QString, ResourceItem*> resources)
{
    beginResetModel();

    QVector<QString> allChildren;
    QMap<QString, QVector<QString>> children;

    for (auto & item : resources)
    {
        if (item->type() == ResourceType::Folder)
        {
            QString filename = QString("%1/%2").arg(GameSettings::rootPath(), item->filename());
            QFile f(filename);
            if (!f.open(QFile::ReadOnly))
            {
                qCritical() << "Error: can't open resource" << item->filename();
            }
            else
            {
                auto doc = QJsonDocument::fromJson(f.readAll());
                auto json = doc.object();

                if (item->type() == ResourceType::Folder)
                {
                    auto childrenJson = json["children"].toArray();
                    for (auto value : childrenJson)
                    {
                        auto child = value.toString();
                        children[item->id()].push_back(child);
                        allChildren.push_back(child);
                    }

                    if (json["isDefaultView"].toBool())
                    {
                        rootItem = resources[item->id()];
                    }
                }

                f.close();
            }
        }
    }

    QVector<ResourceItem*> to_process;
    to_process.push_back(rootItem);
    while (!to_process.isEmpty())
    {
        auto item = to_process.front();
        to_process.pop_front();

        if (item->parentItem != nullptr)
        {
            connect(item, &ResourceItem::nameChanged, this, &ResourcesModel::nameChanged);
        }

        auto c = children[item->id()];
        for(auto & id : c)
        {
            auto res = resources[id];
            res->parentItem = item;
            item->children.push_back(res);
            to_process.push_back(res);
        }
    }

    endResetModel();
}

void ResourcesModel::addItem(ResourceItem * item, QModelIndex parentIndex)
{
    auto parentItem = static_cast<ResourceItem*>(parentIndex.internalPointer());
    int size = parentItem->children.size();

    beginInsertRows(parentIndex, size, size);
    parentItem->children.push_back(item);
    item->parentItem = parentItem;

    connect(item, &ResourceItem::nameChanged, this, &ResourcesModel::nameChanged);

    endInsertRows();
}

void ResourcesModel::removeItem(QModelIndex index)
{
    auto item = static_cast<ResourceItem*>(index.internalPointer());

    beginRemoveRows(index.parent(), index.row(), index.row());
    item->parentItem->children.remove(index.row());
    ResourceItem::remove(item->id());
    endRemoveRows();
}

QModelIndex ResourcesModel::index(int row, int column, const QModelIndex &parent) const
{
    ResourceItem* ptr = nullptr;
    if (!parent.isValid())
        ptr = rootItem;
    else
        ptr = static_cast<ResourceItem*>(parent.internalPointer());
    if (ptr == nullptr) return QModelIndex();
    auto childPtr = ptr->child(row);
    return createIndex(row, column, childPtr);
}

QModelIndex ResourcesModel::parent(const QModelIndex &index) const
{
    auto ptr = static_cast<ResourceItem*>(index.internalPointer());
    if (ptr == nullptr)
        return QModelIndex();
    auto parentPtr = ptr->parentItem;
    if (parentPtr == rootItem)
        return QModelIndex();
    return createIndex(parentPtr->parentItem->children.indexOf(parentPtr), 0, parentPtr);
}

int ResourcesModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        if (rootItem == nullptr) return 0;
        return rootItem->children.size();
    }

    auto ptr = static_cast<ResourceItem*>(parent.internalPointer());
    return ptr->children.size();
}

int ResourcesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant ResourcesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0 && orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return QString("Resources");
    }
    return QVariant();
}

QVariant ResourcesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto ptr = static_cast<ResourceItem*>(index.internalPointer());
    if (role == Qt::DisplayRole)
    {
        return ptr->name();
    }
    else if (role == Qt::DecorationRole)
    {
        return ptr->thumbnail(16, 16);
    }
    else if (ptr->type() == ResourceType::Folder && !index.parent().isValid())
    {
        switch (role)
        {
        case Qt::FontRole:
        {
            QFont f;
            f.setBold(true);
            return f;
        }
        }
    }

    return QVariant();
}

Qt::DropActions ResourcesModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::DropActions ResourcesModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

bool ResourcesModel::removeRows(int row, int count, const QModelIndex & parent)
{
    /*
     * Ugly trick to fix Qt behaviour.
     * After a drop, Qt ask to delete the row the element was before the drag
     * but it's not valid anymore (off by one) if the drag was upwards in the same parent
    */
    if (QT_FIX_DND != -1 && QT_FIX_DND < row)
    {
        row++;
        QT_FIX_DND = -1;
    }

    auto parentItem = static_cast<ResourceItem*>(parent.internalPointer());

    beginRemoveRows(parent, row, row + count - 1);

    parentItem->children.remove(row, count);

    endRemoveRows();

    return true;
}

Qt::ItemFlags ResourcesModel::flags(const QModelIndex & index) const
{
    auto pItem = static_cast<ResourceItem*>(index.internalPointer());

    auto defaultFlags = QAbstractItemModel::flags(index);

    // skip the "root" element
    if (pItem && pItem->parentItem != nullptr)
    {
        // don't allow drag for categories (sound, script, room, etc.)
        // or for OS configuration
        if (pItem->parentItem->type() == ResourceType::Folder)
        {
            auto pFolderItem = qobject_cast<FolderResourceItem*>(pItem->parentItem);
            if (pFolderItem->filterType() == ResourceType::Root
                || pFolderItem->filterType() == ResourceType::Config)
            {
                return Qt::ItemIsDropEnabled | defaultFlags;
            }
            else
            {
                return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
            }
        }
    }

    return defaultFlags;
}

bool ResourcesModel::canDropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) const
{
    Q_UNUSED(action)
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(data)

    if (!parent.isValid())
        return false;

    auto parentItem = static_cast<ResourceItem*>(parent.internalPointer());
    if (parentItem == nullptr)
        return false;

    if (parentItem->type() != ResourceType::Folder)
        return false;
    return true;
}

bool ResourcesModel::dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    if (action == Qt::IgnoreAction)
        return false;

    auto parentItem = static_cast<FolderResourceItem*>(parent.internalPointer());
    auto type = Utils::resourceTypeToString(parentItem->filterType());
    QString itemId = data->data(QString("application/gms2.%1").arg(type));
    auto pItem = ResourceItem::get(itemId);

    beginInsertRows(parent, row, row);
    parentItem->children.insert(row, pItem);
    endInsertRows();

    QT_FIX_DND = row;

    return true;
}

void ResourcesModel::nameChanged()
{
    auto item = qobject_cast<ResourceItem*>(sender());
    if (item)
    {
        auto parent = item->parentItem;
        auto row = parent->children.indexOf(item);
        auto idx = createIndex(row, 0, item);
        emit dataChanged(idx, idx, {Qt::DisplayRole});
    }
}

QStringList ResourcesModel::mimeTypes() const
{
    QStringList types;
    int count = static_cast<int>(ResourceType::Unknown);
    for (int i = 0; i < count; i++)
    {
        types << "application/gms2." + Utils::resourceTypeToString(static_cast<ResourceType>(i));
    }
    return types;
}

QMimeData *ResourcesModel::mimeData(const QModelIndexList & indexes) const
{
    if (indexes.size() != 1) return nullptr;

    QMimeData * pMimeData = new QMimeData();
    auto index = indexes.first();
    auto pItem = static_cast<ResourceItem*>(index.internalPointer());
    auto type = Utils::resourceTypeToString(pItem->type());

    QString mimeType(QString("application/gms2.%1").arg(type));
    pMimeData->setData(mimeType, pItem->id().toLatin1());
    return pMimeData;
}
