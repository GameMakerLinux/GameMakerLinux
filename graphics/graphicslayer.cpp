#include "graphicslayer.h"

GraphicsLayer::GraphicsLayer()
{
}


QRectF GraphicsLayer::boundingRect() const
{
    return QRectF();
}

void GraphicsLayer::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
