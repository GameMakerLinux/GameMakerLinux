#include "spriteimage.h"
#include <QPixmap>

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

QString SpriteImage::frameId() const
{
    return m_frameId;
}

QString SpriteImage::layerId() const
{
    return m_layerId;
}
