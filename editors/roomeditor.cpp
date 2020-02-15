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

#include "roomeditor.h"
#include <QDebug>
#include "utils/utils.h"
#include "graphics/graphicslayer.h"
#include "utils/uuid.h"
#include "resources/spriteresourceitem.h"
#include "gamesettings.h"
#include "resources/dependencies/roomlayer.h"
#include "resources/dependencies/backgroundlayer.h"
#include "resources/dependencies/instancelayer.h"
#include "graphics/graphicsinstance.h"
#include "resources/dependencies/objectinstance.h"
#include "resources/objectresourceitem.h"
#include <QMenu>

RoomEditor::RoomEditor(RoomResourceItem* item)
    : MainEditor { item }
    , ui { new Ui::RoomEditor }
{
    QWidget * w = new QWidget;
    ui->setupUi(w);
    setWidget(w);

    ui->splitter->setSizes({ 50, 300 });

    ui->layersListView->setModel(&layersModel);
    ui->objectsListView->setModel(&objectsModel);
    ui->roomView->setScene(&scene);

    connect(&layersModel, &LayersModel::visibilityChanged, this, &RoomEditor::setLayerVisibility);
    connect(&objectsModel, &ObjectsModel::visibilityChanged, this, &RoomEditor::setInstanceVisibility);
    connect(ui->layersListView, &QListView::pressed, this, &RoomEditor::updateObjectsList);
    connect(ui->objectsListView, &QListView::pressed, this, &RoomEditor::updateSelectedItem);
    connect(ui->objectsListView, &QListView::customContextMenuRequested, this, &RoomEditor::showObjectsListContextMenu);
    connect(&scene, &QGraphicsScene::selectionChanged, this, &RoomEditor::selectedItemChanged);

    scene.setBackgroundBrush(Qt::gray);

    load();
}

RoomEditor::~RoomEditor()
{
    delete ui;
}

void RoomEditor::save()
{
    auto pItem = item<RoomResourceItem>();
    pItem->save();
}

void RoomEditor::load()
{
    auto pItem = item<RoomResourceItem>();

    scene.clear();
    layersModel.clear();
    auto bg = scene.addRect(0, 0, pItem->width() - 1, pItem->height() - 1, QPen(QColor(0, 0, 0)), QBrush(Qt::white));
    bg->setZValue(-999999);

    for (auto & layer : pItem->layers())
    {
        layersModel.addLayer(layer);

        GraphicsLayer * gLayer = new GraphicsLayer;
        graphicsLayers[layer->id()] = gLayer;
        scene.addItem(gLayer);

        if (layer->type() == RoomLayer::Type::Background)
        {
            auto depth = layer->depth();
            gLayer->setZValue(-depth);

            auto bgLayer = qobject_cast<BackgroundLayer*>(layer);
            if (auto sprite = bgLayer->sprite())
            {
                QPixmap pix = sprite->pixmap();
                auto pixItem = scene.addPixmap(pix);
                pixItem->setParentItem(gLayer);
            }
            else
            {
                auto bgColor = scene.addRect(0, 0, pItem->width(), pItem->height(), QPen(), QBrush(bgLayer->colour()));
                bgColor->setParentItem(gLayer);
            }
        }
        else if (layer->type() == RoomLayer::Type::Instances)
        {
            auto instLayer = qobject_cast<InstanceLayer*>(layer);
            for (auto & instance : instLayer->instances())
            {
                auto instItem = new GraphicsInstance(instance);
                instItem->setParentItem(gLayer);
                connect(instItem, &GraphicsInstance::openObject, this, &RoomEditor::openObject);
                connect(instItem, &GraphicsInstance::openInstance, this, &RoomEditor::openInstance);
            }
            gLayer->setCurrent(false);
            //so the instances are always visible
            gLayer->setZValue(1000);
        }
    }
}

void RoomEditor::setLayerVisibility(QString id, bool visible)
{
    graphicsLayers[id]->setVisible(visible);
    ui->layersListView->update();
}

void RoomEditor::updateObjectsList(const QModelIndex & index)
{
    if (!index.isValid())
    {
        return;
    }

    if (m_currentLayer)
    {
        m_currentLayer->setCurrent(false);
        m_currentLayer = nullptr;
    }

    objectsModel.clear();

    auto pLayer = layersModel.layer(index.row());
    if (pLayer->type() == RoomLayer::Type::Instances)
    {
        auto pInstLayer = qobject_cast<InstanceLayer*>(pLayer);
        m_currentLayer = graphicsLayers[pInstLayer->id()];
        m_currentLayer->setCurrent(true);

        for (auto & inst : pInstLayer->instances())
        {
            objectsModel.addObject(inst);
            auto idx = objectsModel.indexOf(inst);
            auto checked = m_currentLayer->isElementVisible(inst);
            auto blocked = objectsModel.blockSignals(true);
            objectsModel.setData(idx, checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
            objectsModel.blockSignals(blocked);
        }
    }
}

void RoomEditor::selectedItemChanged()
{
    auto items = scene.selectedItems();
    if (items.size() == 0)
        return;

    // if more than 1 items are present in the list, the first one is THE ONE we are interested in.
    auto item = items.first();
    auto instanceItem = static_cast<GraphicsInstance*>(item);
    if (instanceItem)
    {
        auto modelIndex = objectsModel.indexOf(instanceItem->objectInstance());
        ui->objectsListView->selectionModel()->select(modelIndex, QItemSelectionModel::ClearAndSelect);
    }
}

void RoomEditor::updateSelectedItem(const QModelIndex & index)
{
    if (!index.isValid())
        return;

    auto pItem = objectsModel.objectInstance(index.row());

    m_currentLayer->selectItem(pItem);
}

void RoomEditor::setInstanceVisibility(QString id, bool visible)
{
    auto pInstance = ResourceItem::get<ObjectInstance>(id);
    m_currentLayer->setElementVisible(pInstance, visible);
}

void RoomEditor::showObjectsListContextMenu(const QPoint & pos)
{
    auto index = ui->objectsListView->indexAt(pos);
    auto inst = objectsModel.objectInstance(index.row());
    if (inst == nullptr)
        return;

    QMenu menu;
    menu.addAction("Edit instance", [this, inst]() {
        emit openInstance(inst);
    });
    menu.addAction("Edit object", [this, inst]() {
        emit openObject(inst->object());
    });
    menu.exec(QCursor::pos());
}
