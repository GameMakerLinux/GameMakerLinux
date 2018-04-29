#ifndef ROOMEDITOR_H
#define ROOMEDITOR_H

#include "maineditor.h"
#include "resources/roomresourceitem.h"
#include "ui_roomeditor.h"
#include "models/layersmodel.h"

class GraphicsLayer;
class RoomEditor : public MainEditor
{
    Q_OBJECT

public:
    explicit RoomEditor(RoomResourceItem* item);
    ~RoomEditor();

protected slots:
    void save() override;
    void reset() override;

private slots:
    void setLayerVisibility(QString id, bool visible);

private:
    Ui::RoomEditor *ui;
    LayersModel model;
    QGraphicsScene scene;
    QMap<QString, GraphicsLayer*> graphicsLayers;
};

#endif // ROOMEDITOR_H
