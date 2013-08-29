#include "ItemListView.h"

ItemListView::ItemListView(QWidget *parent):
    QListView(parent)
{
    scroll_ = new QScrollBar(this);
    scroll_->setRange(0,0);
    scroll_->resize(17,20);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onDoubleClicked(QModelIndex)));
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

ItemListView::~ItemListView()
{

}

QScrollBar *ItemListView::scroll() const
{
    return scroll_;
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

void ItemListView::resizeEvent(QResizeEvent *e)
{
    const QMargins margins = contentsMargins();
    scroll_->resize(scroll_->width(), height() - margins.top() - margins.bottom());
    scroll_->move(width() - scroll_->width() - margins.right(), margins.top());
    emit listResized();
}

void ItemListView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        scroll_->setValue(scroll_->value() - 3);
    }

    if(event->delta() < 0)
    {
        scroll_->setValue(scroll_->value() + 3);
    }
}

void ItemListView::keyPressEvent(QKeyEvent *event)
{
    if(!model())
    {
        return;
    }

    if(event->key() == Qt::Key_Up)
    {
        if(currentIndex().row() == 0)
        {
            if(scroll_->value() > 0)
            {
                scroll_->setValue(scroll_->value() - 1);
            }
        }
    }

    if(event->key() == Qt::Key_Down)
    {
        if(currentIndex().row() == (model()->rowCount() - 1))
        {
            scroll_->setValue(scroll_->value() + 1);
        }
    }

    QListView::keyPressEvent(event);
}

