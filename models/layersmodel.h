#ifndef LAYERSMODEL_H
#define LAYERSMODEL_H

#include <QAbstractListModel>

struct LayerItem
{
    QString id;
    QString name;
    Qt::CheckState visible = Qt::Checked;
    bool locked = false; // unused
};

class LayersModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LayersModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;

    bool setData(const QModelIndex & index, const QVariant & value, int role) override;

    void addLayer(QString id, QString name);

signals:
    void visibilityChanged(QString id, bool visible);

private:
    QVector<LayerItem> items;
};

#endif // LAYERSMODEL_H
