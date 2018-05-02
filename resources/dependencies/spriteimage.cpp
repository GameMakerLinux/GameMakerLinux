#include "spriteimage.h"

SpriteImage::SpriteImage()
    : ResourceItem(ResourceType::SpriteImage)
{
}

void SpriteImage::load(QJsonObject object)
{
    setName("SpriteImage");

    m_frameId = object["FrameId"].toString();
    m_layerId = object["LayerId"].toString();
}
