#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

#include "resources/resourceitem.h"
#include "spriteimage.h"

class SpriteFrame : public ResourceItem
{
public:
    SpriteFrame();

    void load(QJsonObject object) override;

    SpriteImage * compositeImage() const;

private:
    SpriteImage * m_compositeImage = nullptr;
};

#endif // SPRITEFRAME_H
