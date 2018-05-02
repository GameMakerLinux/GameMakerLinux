#include "spriteframe.h"

SpriteFrame::SpriteFrame()
    : ResourceItem(ResourceType::SpriteFrame)
{
}

SpriteImage *SpriteFrame::compositeImage() const
{
    return m_compositeImage;
}


void SpriteFrame::load(QJsonObject object)
{
    setName("SpriteFrame");

    m_compositeImage = new SpriteImage();
    m_compositeImage->load(object["compositeImage"].toObject());
}
