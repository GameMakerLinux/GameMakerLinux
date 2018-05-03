#include "backgroundlayer.h"
#include "utils/uuid.h"
#include "resources/spriteresourceitem.h"

BackgroundLayer::BackgroundLayer()
    : RoomLayer(ResourceType::BackgroundLayer)
{
}

void BackgroundLayer::load(QJsonObject object)
{
    RoomLayer::load(object);

    auto spriteId = object["spriteId"].toString();
    if (!Uuid::isNull(spriteId))
    {
        m_sprite = ResourceItem::get<SpriteResourceItem>(spriteId);
    }
}

SpriteResourceItem *BackgroundLayer::sprite() const
{
    return m_sprite;
}
