#include "ItemModelList.h"

ItemModelList::ItemModelList(QObject *parent):
    QAbstractItemModel(parent)
{
}

QModelIndex ItemModelList::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex ItemModelList::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ItemModelList::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int ItemModelList::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant ItemModelList::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

void ItemModelList::addPointList(const PointList &pointList)
{
}
