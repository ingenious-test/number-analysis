#ifndef ITEMLISTMODEL_H

#define ITEMLISTMODEL_H

#include <QAbstractListModel>

#include "AbstractAnalysis.h"

typedef QString ID;

typedef QList<ID> IDList;

class ItemListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ItemListModel(QObject *parent = 0);
    ItemListModel(const SequencePointList &seqPointList, QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent  = QModelIndex()) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;


 private:
    SequencePointList sequencePointList_;

};

#endif // ITEMLISTMODEL_H
