#include "ItemListModel.h"

ItemListModel::ItemListModel(AbstractPointListReader *reader,
                             QObject *parent):
    QAbstractListModel(parent),
    reader_(reader)
{
   update();
}

ItemListModel::ItemListModel(const IDList &items, QObject *parent):
    QAbstractListModel(parent)
{
    appendPointList(items);
}

void ItemListModel::update()
{
    items_.clear();
    items_ = reader_->readAllItems();
    //appendPointList(reader_->readAllItems());
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
    return items_.count();
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

            return items_[index.row()];

        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
}

void ItemListModel::appendPointList_(const ID &id)
{
    if(id.isNull())
    {
        qWarning() << "ID not set";
    }

    if(!items_.contains(id))
    {
        items_.append(id);
    }
    else
    {
        qWarning() << QString("ItemListModel contains ID: %1").arg(id);
    }
}

void ItemListModel::appendPointList(const ID &id)
{
    appendPointList_(id);
    qSort(items_);
}

void ItemListModel::appendPointList(const IDList &items)
{
    foreach(const ID& id, items)
    {
        appendPointList_(id);
    }
    qSort(items_);
}
