#include "uuid.h"
#include <QUuid>

bool Uuid::isNull(QString uuid)
{
    return QUuid(uuid).isNull();
}
