#ifndef ITEMLISTVIEW_H

#define ITEMLISTVIEW_H

#include <QtGui/QListView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QScrollBar>
#include "AbstractAnalysis.h"

class ItemListView :public QListView
{
    Q_OBJECT
public:
    ItemListView(QWidget *parent = 0);
    ~ItemListView();

private slots:
    void onDoubleClicked(QModelIndex index);
    void contextMenuEvent(QContextMenuEvent *);

    void onSelectedAllClick();
    void onAddToAnalysisClick();


signals:
    void itemActivated(const ID &item);
    void itemsActivated(const IDList &items);
};

#endif // ITEMLISTVIEW_H
