#include "ItemListView.h"

ItemListView::ItemListView(QWidget *parent):
    QListView(parent)
{
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SIGNAL(doubleClicked(QModelIndex)));
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

ItemListView::~ItemListView()
{

}

void ItemListView::onDoubleClicked(QModelIndex index)
{
    ID id = index.data().toString();
    emit itemActivated(id);
}



void ItemListView::contextMenuEvent(QContextMenuEvent *a)
{
    QMenu menu;
    menu.addAction("Выделить все", this, SLOT(onSelectedAllClick()));
    menu.addAction("Добавить к анализу", this, SLOT(onAddToAnalysisClick()));
    menu.exec(a->globalPos());
}

void ItemListView::onSelectedAllClick()
{
    selectAll();
}

void ItemListView::onAddToAnalysisClick()
{
    IDList items;
    foreach(const QModelIndex& index, selectedIndexes())
    {
        items.append(index.data().toString());
    }

    if(!items.isEmpty())
    {
        emit itemsActivated(items);
    }
}

