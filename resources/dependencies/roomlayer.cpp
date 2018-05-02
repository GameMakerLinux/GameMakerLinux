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
