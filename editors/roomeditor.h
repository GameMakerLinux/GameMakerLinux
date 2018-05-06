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

#ifndef ROOMEDITOR_H
#define ROOMEDITOR_H

#include "maineditor.h"
#include "resources/roomresourceitem.h"
#include "ui_roomeditor.h"
#include "models/layersmodel.h"
#include "models/objectsmodel.h"

class GraphicsLayer;
class ObjectResourceItem;
class RoomEditor : public MainEditor
{
    Q_OBJECT

public:
    explicit RoomEditor(RoomResourceItem* item);
    ~RoomEditor();

signals:
    void openObject(ObjectResourceItem * item);
    void openInstance(ObjectInstance* item);

protected slots:
    void save() override;
    void reset() override;

private slots:
    void setLayerVisibility(QString id, bool visible);
    void updateObjectsList(const QModelIndex & index);
    void selectedItemChanged();
    void updateSelectedItem(const QModelIndex & index);
    void setInstanceVisibility(QString id, bool visible);
    void showObjectsListContextMenu(const QPoint & pos);

private:
    Ui::RoomEditor *ui;
    LayersModel layersModel;
    ObjectsModel objectsModel;
    QGraphicsScene scene;
    QMap<QString, GraphicsLayer*> graphicsLayers;
    GraphicsLayer * m_currentLayer = nullptr;
};

#endif // ROOMEDITOR_H
