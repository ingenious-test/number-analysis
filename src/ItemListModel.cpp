#include "ItemListModel.h"

ItemListModel::ItemListModel(AbstractPointListReader *reader,
                             QObject *parent):
    QAbstractListModel(parent),
    reader_(reader),
    startOutItem_(0),
    outItemsCount_(0)
{
    update();
}

ItemListModel::ItemListModel(const IDList &items, QObject *parent):
    QAbstractListModel(parent),
    startOutItem_(0),
    outItemsCount_(0)
{
    appendPointList(items);
}

void ItemListModel::update()
{
    items_.clear();
    appendPointList(reader_->readAllItems());
    emit dataChanged();
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
    return outItemsCount_ == 0 ? items_.size() : outItemsCount_;
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
            if(outItemsCount_ == 0)
            {
                return items_[index.row()];
            }
            else
            {
                //int ind = (currentPage_ * itemsCountOnPage_) + index.row();
                const int ind = startOutItem_ + index.row();
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
    emit dataChanged();
}

void ItemListModel::appendPointList(const IDList &items)
{
    foreach(const ID& id, items)
    {
        appendPointList_(id);
    }
    qSort(items_);
    emit dataChanged();
}


void ItemListModel::setOutItemsCount(const int count)
{
    if(count >= 0)
    {
        outItemsCount_ = count;
        emit itemsCountOnPageChanged();
        if(startOutItem_ >= lastStartOutItem())
        {
            setStartOutItem(0);
        }

        reset();
    }
}

int ItemListModel::outItemsCount() const
{
    return outItemsCount_;
}

int ItemListModel::startOutItem() const
{
    return startOutItem_;
}

void ItemListModel::setStartOutItem(const int page)
{
    if(page >= 0 && page <= lastStartOutItem())
    {
        startOutItem_ = page;
        emit currentPageChanged();
        reset();
    }
}

int ItemListModel::lastStartOutItem() const
{
    if(outItemsCount_ == 0)
    {
        return 1;
    }

    if(items_.isEmpty())
    {
        return 0;
    }

    return items_.count() - outItemsCount_;
}
