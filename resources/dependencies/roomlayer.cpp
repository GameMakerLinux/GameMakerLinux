#include "roomlayer.h"

RoomLayer::RoomLayer(ResourceType type)
    : ResourceItem(type)
{
}

int RoomLayer::depth() const
{
    return m_depth;
}

void RoomLayer::setDepth(int d)
{
    m_depth = d;
}

void RoomLayer::load(QJsonObject object)
{
    id = object["id"].toString();
    setName(object["name"].toString());
    setDepth(object["depth"].toInt());
}
