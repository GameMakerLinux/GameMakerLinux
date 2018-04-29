#ifndef UUID_H
#define UUID_H

#include <QString>

class Uuid
{
public:
    Uuid() = delete;

    static bool isNull(QString uuid);
};

#endif // UUID_H
