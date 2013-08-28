#include "ItemListView.h"

ItemListView::ItemListView(QWidget *parent):
    QListView(parent)
{
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClicked(QModelIndex)));
}

ItemListView::~ItemListView()
{

}

void ItemListView::doubleClicked(const QModelIndex &index)
{
    ID id = index.data().toString();
    emit itemActivated(id);
}

