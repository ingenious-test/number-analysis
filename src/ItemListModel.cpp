#include "ItemListModel.h"

ItemListModel::ItemListModel(QObject *parent):
    QAbstractListModel(parent)
{

}

ItemListModel::ItemListModel(const SequencePointList &seqPointList, QObject *parent):
    QAbstractListModel(parent)
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
    return 1;
}

QVariant ItemListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        if(index.column() == 0)
        {
            return QVariant::fromValue(sequencePointList_[index.row()]);
        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
}
