/*
    Copyright (C) 2018  Alexander Roper

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
