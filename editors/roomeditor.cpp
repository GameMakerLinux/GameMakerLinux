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

#include "roomeditor.h"
#include "utils/utils.h"
#include "graphics/graphicslayer.h"
#include "utils/uuid.h"
#include "resources/spriteresourceitem.h"
#include "gamesettings.h"
#include "resources/dependencies/roomlayer.h"
#include "resources/dependencies/backgroundlayer.h"
#include "resources/dependencies/instancelayer.h"
#include "resources/dependencies/tilelayer.h"
#include "resources/dependencies/folderlayer.h"
#include "graphics/graphicsinstance.h"
#include "resources/dependencies/objectinstance.h"
#include "resources/objectresourceitem.h"
#include <QMenu>
#include <QDragEnterEvent>
#include <QMimeData>

RoomEditor::RoomEditor(RoomResourceItem* item)
    : MainEditor { item }
    , ui { new Ui::RoomEditor }
{
    QWidget * w = new QWidget;
    ui->setupUi(w);
    setWidget(w);

    ui->splitter->setSizes({ 50, 300 });

    ui->layersTreeView->setModel(&layersModel);
    ui->objectsListView->setModel(&objectsModel);
    ui->roomView->setScene(&scene);
    ui->roomView->viewport()->setAcceptDrops(true);
    ui->roomView->viewport()->installEventFilter(this);

    connect(&layersModel, &LayersModel::visibilityChanged, this, &RoomEditor::setLayerVisibility);
    connect(&objectsModel, &ObjectsModel::visibilityChanged, this, &RoomEditor::setInstanceVisibility);
    connect(ui->layersTreeView, &QListView::pressed, this, &RoomEditor::updateObjectsList);
    connect(ui->objectsListView, &QListView::pressed, this, &RoomEditor::updateSelectedItem);
    connect(ui->objectsListView, &QListView::customContextMenuRequested, this, &RoomEditor::showObjectsListContextMenu);
    connect(&scene, &QGraphicsScene::selectionChanged, this, &RoomEditor::selectedItemChanged);

    scene.setBackgroundBrush(Qt::gray);

    load();

    ui->layersTreeView->setCurrentIndex(layersModel.index(0, 0, QModelIndex()));
    ui->layersTreeView->pressed(layersModel.index(0, 0, QModelIndex()));
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
    auto bg = scene.addRect(0, 0, pItem->width() - 1, pItem->height() - 1, QPen(QColor(0, 0, 0)), QBrush(Qt::white));
    bg->setZValue(-999999);

    layersModel.load(pItem);

    for (auto & layer : pItem->layers())
    {
        // folders don't render anything.
        if (layer->type() == RoomLayer::Type::Folder)
        {
            continue;
        }

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
                createInstance(instance, gLayer);
            }
            gLayer->setCurrent(false);
            //so the instances are always visible
            gLayer->setZValue(1000);
        }
        else if (layer->type() == RoomLayer::Type::Tiles)
        {
            auto tileLayer = qobject_cast<TileLayer*>(layer);
            auto depth = layer->depth();
            gLayer->setZValue(-depth);

            auto pix = tileLayer->render();
            auto pixItem = scene.addPixmap(pix);
            pixItem->setParentItem(gLayer);
        }
    }
}

void RoomEditor::setLayerVisibility(RoomLayer * layer, bool visible)
{
    if (layer->type() == RoomLayer::Type::Folder)
    {
        auto folderLayer = qobject_cast<FolderLayer*>(layer);
        for (auto & child : folderLayer->subLayers())
        {
            setLayerVisibility(child, visible);
        }
    }
    else
    {
        graphicsLayers[layer->id()]->setVisible(visible);
    }

    ui->layersTreeView->update();
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

    auto pLayer = static_cast<LayerItem*>(index.internalPointer())->layer;
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


bool RoomEditor::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == ui->roomView->viewport())
    {
        if (event->type() == QEvent::DragEnter || event->type() == QEvent::DragMove)
        {
            auto dragEvent = static_cast<QDragEnterEvent*>(event);
            if (dragEvent->mimeData()->hasFormat("application/gms2.GMObject"))
            {
                auto id = dragEvent->mimeData()->data("application/gms2.GMObject");
                if (acceptObjectOnCurrentLayer(id))
                {
                    dragEvent->acceptProposedAction();
                }
            }
            return true;
        }
        else if (event->type() == QEvent::Drop)
        {
            auto dropEvent = static_cast<QDropEvent*>(event);
            auto id = dropEvent->mimeData()->data("application/gms2.GMObject");
            auto objItem = ResourceItem::get<ObjectResourceItem>(id);
            auto gInst = createInstance(objItem);
            gInst->setPos(ui->roomView->mapToScene(dropEvent->pos()));
            return true;
        }
    }
    return false;
}

bool RoomEditor::acceptObjectOnCurrentLayer(QString id)
{
    auto item = ResourceItem::get(id);
    auto modelIndex = ui->layersTreeView->selectionModel()->currentIndex();
    auto layer = static_cast<LayerItem*>(modelIndex.internalPointer())->layer;
    return layer->acceptObject(item);
}

GraphicsInstance * RoomEditor::createInstance(ObjectResourceItem * item)
{
    auto objInst = new ObjectInstance(item);
    auto modelIndex = ui->layersTreeView->selectionModel()->currentIndex();
    auto layerItem = static_cast<LayerItem*>(modelIndex.internalPointer())->layer;
    auto layer = static_cast<InstanceLayer*>(layerItem);
    layer->addInstance(objInst);
    objectsModel.addObject(objInst);

    auto gLayer = graphicsLayers[layer->id()];
    return createInstance(objInst, gLayer);
}

GraphicsInstance * RoomEditor::createInstance(ObjectInstance * instance, GraphicsLayer * layer)
{
    auto instItem = new GraphicsInstance(instance);
    instItem->setParentItem(layer);
    connect(instItem, &GraphicsInstance::openObject, this, &RoomEditor::openObject);
    connect(instItem, &GraphicsInstance::openInstance, this, &RoomEditor::openInstance);

    return instItem;
}
