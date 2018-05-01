#ifndef EVENTSMODEL_H
#define EVENTSMODEL_H

#include <QAbstractListModel>

class ObjectEvent;

struct EventItem
{
    ObjectEvent * event = nullptr;
    bool modified = false;
};

class EventsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit EventsModel(QObject *parent = nullptr);

    void addEvent(ObjectEvent * event);
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QString getFilename(int row) const;
    void setModified(int row, bool modified);

private:
    QVector<EventItem> items;
};

#endif // EVENTSMODEL_H
