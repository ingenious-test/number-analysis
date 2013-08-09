#include "ItemListModel.h"

ItemListModel::ItemListModel(QObject *parent):
    QAbstractItemModel(parent)
{
}

ItemListModel::ItemListModel(const SequencePointList &seqPointList, QObject *parent)
{
    foreach(PointList pointList, seqPointList)
    {
        sequencePointList_.append(pointList);
    }
}

QModelIndex ItemListModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex ItemListModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ItemListModel::rowCount(const QModelIndex &parent) const
{
    return sequencePointList_.size();
}

int ItemListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ItemListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        IDList listResults = sequencePointList_.getIDs();
        if(index.column() == 0)
        {
            return sequencePointList_.at(index.row()).id();
        }

        if(index.column() == 1)
        {
            return sequencePointList_.at(index.row()).join();
        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
}

void ItemListModel::addPointList(const PointList &pointList)
{
}
