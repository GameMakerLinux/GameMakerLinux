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

#include "folderresourceitem.h"
#include "utils/utils.h"
#include <QDebug>

FolderResourceItem::FolderResourceItem()
    : ResourceItem { ResourceType::Folder }
{
}

void FolderResourceItem::load(QJsonObject object)
{
    m_filterType = Utils::resourceStringToType(object["filterType"].toString());
    m_folderName = object["folderName"].toString();
    m_isDefaultView = object["isDefaultView"].toBool();
    m_localisedFolderName = object["localisedFolderName"].toString();

    setName(m_folderName);
}


QJsonObject FolderResourceItem::save()
{
    QJsonObject object;
    object["id"] = id;
    object["modelName"] = Utils::resourceTypeToString(type());
    object["mvc"] = "1.1";
    object["name"] = id;
    object["filterType"] = Utils::resourceTypeToString(m_filterType);
    object["folderName"] = m_folderName;
    object["isDefaultView"] = m_isDefaultView;
    object["localisedFolderName"] = m_localisedFolderName;

    QJsonArray childrenJson;
    for (auto & child : children)
    {
        childrenJson.append(child->id);
    }
    object["children"] = childrenJson;

    return object;
}

ResourceType FolderResourceItem::filterType() const
{
    return m_filterType;
}

bool FolderResourceItem::isLocalised() const
{
    return !m_localisedFolderName.isEmpty();
}
