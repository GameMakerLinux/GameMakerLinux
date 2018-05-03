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

#ifndef FOLDERRESOURCEITEM_H
#define FOLDERRESOURCEITEM_H

#include "resourceitem.h"

class FolderResourceItem : public ResourceItem
{
    Q_OBJECT

public:
    FolderResourceItem();

    void load(QJsonObject object) override;
    void save() override;

    ResourceType filterType() const;
    bool isLocalised() const;

private:
    ResourceType m_filterType;
    QString m_folderName;
    bool m_isDefaultView = false;
    QString m_localisedFolderName;
};

#endif // FOLDERRESOURCEITEM_H
