#ifndef SPRITEIMAGE_H
#define SPRITEIMAGE_H

#include "resources/resourceitem.h"

class SpriteImage : public ResourceItem
{
public:
    SpriteImage();

    void load(QJsonObject object) override;

    QString frameId() const;
    QString layerId() const;

private:
    QString m_frameId;
    QString m_layerId;
};

#endif // SPRITEIMAGE_H
