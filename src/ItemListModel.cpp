#include "ItemListModel.h"

ItemListModel::ItemListModel(AbstractPointListReader *reader,
                             QObject *parent):
    QAbstractListModel(parent),
    reader_(reader)
{
    setPage(0);
    setItemsCountOnPage(0);
    update();
}

ItemListModel::ItemListModel(const IDList &items, QObject *parent):
    QAbstractListModel(parent),
    page_(0),
    itemsOnPage_(0)
{
    appendPointList(items);
}

void ItemListModel::update()
{
    clear();
    appendPointList(reader_->readAllItems());
    this->reset();
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
    if(page_ + 1 == pagesCount())
    {
        const int rows = (pagesCount() * itemsOnPage_) - items_.count();
        return itemsOnPage_ - rows;
    }

    return itemsOnPage_ == 0 ? items_.size() : itemsOnPage_;
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
            if(itemsOnPage_ == 0)
            {
                return items_[index.row()];
            }
            else
            {
                int ind = (page_ * itemsOnPage_) + index.row();
                if(ind >= 0 && ind < items_.count())
                {
                    return items_[ind];
                }
            }
        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
}

bool ItemListModel::appendPointList(const ID &id)
{
    if(id.isNull())
    {
        qWarning() << "ID not set";
        return false;
    }

    if(!items_.contains(id))
    {
        items_.append(id);

        return true;
    }
    else
    {
        qWarning() << QString("ItemListModel contains ID: %1").arg(id);
        return false;
    }
    return false;
}

void ItemListModel::appendPointList(const IDList &items)
{
    foreach(const ID& id, items)
    {
        appendPointList(id);
    }
    qSort(items_);
}

void ItemListModel::clear()
{
    items_.clear();
}

void ItemListModel::setItemsCountOnPage(const int count)
{
    if(count >= 0 && count < items_.count())
    {
        itemsOnPage_ = count;
        reset();
    }
}

int ItemListModel::pagesCount() const
{
    if(itemsOnPage_ == 0)
    {
        return 1;
    }

    if(items_.isEmpty())
    {
        return 1;
    }

    int pages  = items_.count() / itemsOnPage_;
    if(items_.count() % itemsOnPage_ != 0)
    {
        pages++;
    }
    return pages;
}

const int ItemListModel::page() const
{
    return page_;
}

void ItemListModel::setPage(const int page)
{
    if(page >= 0 && page < pagesCount())
    {
        page_ = page;
        emit pageChanged();
        reset();
    }
}
