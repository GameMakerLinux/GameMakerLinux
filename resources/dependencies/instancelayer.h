#ifndef INSTANCELAYER_H
#define INSTANCELAYER_H

#include "roomlayer.h"

class InstanceLayer : public RoomLayer
{
    Q_OBJECT

public:
    InstanceLayer();

    void load(QJsonObject object);
};

#endif // INSTANCELAYER_H
