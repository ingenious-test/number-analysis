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

    QScrollBar* scroll() const;
    int contentsHeight() {return contentsSize().height();}

private slots:
    void onDoubleClicked(QModelIndex index);
    void contextMenuEvent(QContextMenuEvent *);

    void onSelectedAllClick();
    void onAddToAnalysisClick();

    void resizeEvent(QResizeEvent *e);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);


private:
    QScrollBar* scroll_;

signals:
    void itemActivated(const ID &item);
    void itemsActivated(const IDList &items);
    void listResized();
};

#endif // ITEMLISTVIEW_H
