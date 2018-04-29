#ifndef EVENTSMODEL_H
#define EVENTSMODEL_H

#include <QAbstractListModel>

struct EventItem
{
    QString name;
    QString filename;
};

class EventsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit EventsModel(QObject *parent = nullptr);

    void addEvent(QString name, QString filename);
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QString getFilename(int row) const;

private:
    QVector<EventItem> items;
};

#endif // EVENTSMODEL_H
