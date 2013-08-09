#ifndef ITEMLISTDELEGATE_H

#define ITEMLISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "AbstractAnalysis.h"


class ItemListDelegate : public QStyledItemDelegate
{
public:
    ItemListDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    const QString& pointsSep();
    void setPointsSep(const QString& pointsSep);

private:
    QString pointsSep_;
};

#endif // ITEMLISTDELEGATE_H
