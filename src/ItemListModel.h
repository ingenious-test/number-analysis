#ifndef ITEMLISTMODEL_H

#define ITEMLISTMODEL_H

#include <QAbstractListModel>

#include "../mocs/MocPointListReader.h"

#include "AbstractAnalysis.h"

typedef QString ID;

typedef QList<ID> IDList;

class ItemListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ItemListModel(AbstractPointListReader *reader,
                  QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent  = QModelIndex()) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void appendPointList(const ID& id);
    void appendPointList(const IDList &items);

protected:
    ItemListModel(const IDList &items, QObject *parent = 0);

private:
    IDList items_;
    AbstractPointListReader *reader_;

    void appendPointList_(const ID& id);

public slots:
    void update();

};

#endif // ITEMLISTMODEL_H
