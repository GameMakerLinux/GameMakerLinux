#ifndef ROOMLAYER_H
#define ROOMLAYER_H

#include "resources/resourceitem.h"

class RoomLayer : public ResourceItem
{
public:
    RoomLayer(ResourceType type);

    int depth() const;

protected:
    void setDepth(int d);

private:
    int m_depth;
};

#endif // ROOMLAYER_H
