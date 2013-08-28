#include "ItemListView.h"

ItemListView::ItemListView(QWidget *parent):
    QListView(parent)
{
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoubleClicked(QModelIndex)));
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


    QAction* actAddToAnalysis = menu.addAction("Добавить к анализу", this, SLOT(onAddToAnalysisClick()));
    actAddToAnalysis->setEnabled(!selectedIndexes().isEmpty());
    if(selectedIndexes().count() > 1)
    {
        actAddToAnalysis->setText(actAddToAnalysis->text()
                                  + "(" + QString::number(selectedIndexes().count()) + ")");

        QFont font = actAddToAnalysis->font();
        font.setBold(true);
        actAddToAnalysis->setFont(font);
    }

    menu.addAction("Выделить все", this, SLOT(onSelectedAllClick()));

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

