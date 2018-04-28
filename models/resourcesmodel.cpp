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

#include "resourcesmodel.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

ResourcesModel::ResourcesModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

void ResourcesModel::fill(QMap<QString, ResourceItem*> resources)
{
    beginResetModel();

    QVector<QString> allChildren;
    QMap<QString, QVector<QString>> children;

    for (auto & item : resources)
    {
        if (item->type == ResourceType::MainOptions)
        {
            item->load(QJsonObject());
            continue;
        }

        QFile f(item->filename);
        if (!f.open(QFile::ReadOnly))
        {
            qCritical() << "Error: can't open resource" << item->filename;
        }
        else
        {
            auto doc = QJsonDocument::fromJson(f.readAll());
            auto json = doc.object();

            if (item->type == ResourceType::Folder)
            {
                auto childrenJson = json["children"].toArray();
                for (const auto & value : childrenJson)
                {
                    auto child = value.toString();
                    children[item->id].push_back(child);
                    allChildren.push_back(child);
                }

                if (json["filterType"].toString() == "root")
                {
                    rootItem.reset(resources[item->id]);
                }
            }

            item->load(json);

            f.close();
        }
    }

    QVector<ResourceItem*> to_process;
    to_process.push_back(rootItem.data());
    while (!to_process.isEmpty())
    {
        auto item = to_process.front();
        to_process.pop_front();

        if (item->parentItem != nullptr)
        {
            connect(item, &ResourceItem::nameChanged, [this, item]() {
                ResourceItem* parent = item->parentItem;
                int row = parent->children.indexOf(item);
                auto idx = createIndex(row, 0, item);
                emit dataChanged(idx, idx, {Qt::DisplayRole});
            });
        }

        auto c = children[item->id];
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

QModelIndex ResourcesModel::index(int row, int column, const QModelIndex &parent) const
{
    ResourceItem* ptr = nullptr;
    if (!parent.isValid())
        ptr = rootItem.data();
    else
        ptr = static_cast<ResourceItem*>(parent.internalPointer());
    auto childPtr = ptr->child(row);
    return createIndex(row, column, childPtr);
}

QModelIndex ResourcesModel::parent(const QModelIndex &index) const
{
    auto ptr = static_cast<ResourceItem*>(index.internalPointer());
    auto parentPtr = ptr->parentItem;
    if (parentPtr == rootItem.data())
        return QModelIndex();
    return createIndex(parentPtr->children.indexOf(ptr), 0, parentPtr);
}

int ResourcesModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        if (rootItem.isNull()) return 0;
        return rootItem->children.size();
    }

    auto ptr = static_cast<ResourceItem*>(parent.internalPointer());
    return ptr->children.size();
}

int ResourcesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant ResourcesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        auto ptr = static_cast<ResourceItem*>(index.internalPointer());
        return ptr->name();
    }

    return QVariant();
}

static QMap<QString, ResourceType> resourcesTypesStrings = {
    { "GMFolder",           ResourceType::Folder            },
    { "GMObject",           ResourceType::Object            },
    { "GMRoom",             ResourceType::Room              },
    { "GMSprite",           ResourceType::Sprite            },
    { "GMScript",           ResourceType::Script            },
    { "GMMainOptions",      ResourceType::MainOptions,      },
    { "GMiOSOptions",       ResourceType::iOSOptions,       },
    { "GMIncludedFile",     ResourceType::IncludedFile,     },
    { "GMAmazonFireOptions",ResourceType::AmazonFireOptions,},
    { "GMLinuxOptions",     ResourceType::LinuxOptions,     },
    { "GMWindowsOptions",   ResourceType::WindowsOptions,   },
    { "GMAndroidOptions",   ResourceType::AndroidOptions,   },
    { "GMMacOptions",       ResourceType::MacOptions,       }
};

QString ResourceTypeToString(ResourceType type)
{
    return resourcesTypesStrings.key(type, "Unknown");
}

ResourceType ResourceStringToType(QString type)
{
    if (resourcesTypesStrings.contains(type))
    {
        return resourcesTypesStrings[type];
    }
    qDebug() << "unknown type:" << type;
    return ResourceType::Unknown;
}
