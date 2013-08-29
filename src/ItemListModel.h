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

    int seqCount() const { return items_.count();}

    void setOutItemsCount(const int count);
    int outItemsCount() const;

    int startOutItem() const;
    void setStartOutItem(const int page);

    int lastStartOutItem() const;

protected:
    ItemListModel(const IDList &items, QObject *parent = 0);

private:
    IDList items_;
    AbstractPointListReader *reader_;

    int startOutItem_;
    int outItemsCount_;

    void appendPointList_(const ID& id);

public slots:
    void update();

signals:
    void currentPageChanged();
    void itemsCountOnPageChanged();
    void dataChanged();
};

#endif // ITEMLISTMODEL_H
