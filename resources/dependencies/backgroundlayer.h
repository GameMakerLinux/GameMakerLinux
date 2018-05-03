#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include "roomlayer.h"

class BackgroundLayer : public RoomLayer
{
    Q_OBJECT

public:
    BackgroundLayer();

    void load(QJsonObject object);

    SpriteResourceItem * sprite() const;

private:
    SpriteResourceItem * m_sprite = nullptr;
};

#endif // BACKGROUNDLAYER_H
