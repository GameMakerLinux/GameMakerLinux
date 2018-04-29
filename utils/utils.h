#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class Utils
{
public:
    Utils() = delete;

    static QJsonObject readFile(QString filename);
};

#endif // UTILS_H
