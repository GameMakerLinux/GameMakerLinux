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

RoomEditor::RoomEditor(RoomResourceItem* item)
    : MainEditor(item)
    , ui(new Ui::RoomEditor)
{
    QWidget * w = new QWidget;
    ui->setupUi(w);
    setWidget(w);

    ui->splitter->setSizes({ 50, 300 });

    ui->layersListView->setModel(&model);
    ui->roomView->setScene(&scene);

    connect(&model, &LayersModel::visibilityChanged, this, &RoomEditor::setLayerVisibility);

    reset();
}

RoomEditor::~RoomEditor()
{
    delete ui;
}

void RoomEditor::save()
{
    auto pItem = item<RoomResourceItem>();
    pItem->save();

    setDirty(false);
}

void RoomEditor::reset()
{
    auto pItem = item<RoomResourceItem>();

    auto json = Utils::readFileToJSON(pItem->filename);
    if (json.isEmpty())
    {
        return;
    }

    auto layers = json["layers"].toArray();
    for (const auto & value : layers)
    {
        auto layer = value.toObject();
        auto id = layer["id"].toString();
        auto name = layer["name"].toString();

        model.addLayer(id, name);

        GraphicsLayer * gLayer = new GraphicsLayer;
        graphicsLayers[id] = gLayer;
        scene.addItem(gLayer);

        auto depth = layer["depth"].toInt();
        gLayer->setZValue(-depth);

        auto spriteId = layer["spriteId"].toString();
        if (!Uuid::isNull(spriteId))
        {
            auto pItem = ResourceItem::get(spriteId);
            if (pItem)
            {
                auto spriteItem = qobject_cast<SpriteResourceItem*>(pItem);
                auto json = Utils::readFileToJSON(spriteItem->filename);
                if (!json.isEmpty())
                {
                    auto imageName = json["frames"].toArray().first().toObject()["id"].toString();
                    auto fullPath = QString("%1/sprites/%2/%3.png").arg(GameSettings::rootPath(), spriteItem->name(), imageName);
                    auto pix = scene.addPixmap(QPixmap(fullPath));
                    pix->setParentItem(gLayer);
                }
            }
        }
    }
}

void RoomEditor::setLayerVisibility(QString id, bool visible)
{
    graphicsLayers[id]->setVisible(visible);
    ui->layersListView->update();

    setDirty();
}
