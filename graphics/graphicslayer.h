#ifndef GRAPHICSLAYER_H
#define GRAPHICSLAYER_H

#include <QGraphicsItem>

class GraphicsLayer : public QGraphicsItem
{
public:
    GraphicsLayer();

    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

#endif // GRAPHICSLAYER_H
