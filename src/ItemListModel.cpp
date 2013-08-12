#include "ItemListModel.h"

ItemListModel::ItemListModel(QObject *parent):
    QAbstractListModel(parent)
{

}

ItemListModel::ItemListModel(const IDList &idList, QObject *parent):
    QAbstractListModel(parent)
{
   appendPointList(idList);
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
    return idList_.size();
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
            return idList_[index.row()];
        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
}

void ItemListModel::appendPointList(const ID &id)
{
    if(id.isEmpty())
    {
        qWarning() << "ID not set";
        return;
    }

    if(!idList_.contains(id))
    {
        idList_.append(id);
    }
    else
    {
        qWarning() << QString("ItemListModel contains ID: %1").arg(id);
    }

}

void ItemListModel::appendPointList(const IDList &idList)
{
    foreach(const ID& id, idList)
    {
        appendPointList(id);
    }
}
