#ifndef ITEMLISTVIEW_H

#define ITEMLISTVIEW_H

#include <QtGui/QListView>
#include <QScrollBar>
#include "AbstractAnalysis.h"

class ItemListView :public QListView
{
    Q_OBJECT
public:
    ItemListView(QWidget *parent = 0);
    ~ItemListView();

private slots:
    void doubleClicked(const QModelIndex &index);


signals:
    void itemActivated(const ID &item);
};

#endif // ITEMLISTVIEW_H
