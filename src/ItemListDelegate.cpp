#include "ItemListDelegate.h"

ItemListDelegate::ItemListDelegate():
    pointsSep_(" : ")
{
}

void ItemListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);
    painter->save();

    PointList pointList = index.data().value<PointList>();

    painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft, pointList.id() + "\r\n\t" + pointList.join());

    painter->restore();
}

QSize ItemListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    PointList pointList = index.data().value<PointList>();

    QFont f = option.font;
    QFontMetrics fm(f);

    return QSize(fm.width(pointList.id()), fm.height()*2);
}

const QString &ItemListDelegate::pointsSep()
{
    return pointsSep_;
}

void ItemListDelegate::setPointsSep(const QString &pointsSep)
{
    pointsSep_ = pointsSep;
}
