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

#ifndef ROOMRESOURCEITEM_H
#define ROOMRESOURCEITEM_H

#include "resourceitem.h"
#include "dependencies/roomsettings.h"

class FolderLayer;
class RoomResourceItem : public ResourceItem
{
    Q_OBJECT

public:
    RoomResourceItem();

    void load(QJsonObject object) override;
    QString filename() const override;

    int height() const;
    int width() const;

    QVector<RoomLayer *> layers() const;
    QVector<RoomLayer *> rootLayers() const;

private:
    void loadSubLayers(FolderLayer * parentLayer, QJsonArray layers);
    QVector<RoomLayer *> m_layers;
    QVector<RoomLayer *> m_rootLayers;
    RoomSettings m_settings;
};

#endif // ROOMRESOURCEITEM_H
