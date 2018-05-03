#include "instancelayer.h"

InstanceLayer::InstanceLayer()
    : RoomLayer(ResourceType::InstanceLayer)
{
}

void InstanceLayer::load(QJsonObject object)
{
    RoomLayer::load(object);
}
