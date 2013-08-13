#include "AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;

    AnalysisList list;
    list << new StupidAnalysis(1.0)
         << new AverageIgnoreNullAnalysis()
         << new AverageAnalysis;

    analyzesModel_ = new AnalysisTableModel(list);

    analyzesView_ = new QTableView();

    analyzesView_->setModel(analyzesModel_);

    seqPointListModel_ = new ItemListModel();

    seqPointListView_ = new ItemListView();
    seqPointListView_->setFixedWidth(300);
    seqPointListView_->setModel(seqPointListModel_);

    mainLayout->addWidget(seqPointListView_);
    mainLayout->addWidget(analyzesView_);


    setLayout(mainLayout);

    connect(seqPointListView_, SIGNAL(itemActivated(ID)), this, SLOT(addItem(ID)));
}

AnalysisWindow::~AnalysisWindow()
{
    disconnect(seqPointListView_, SIGNAL(itemActivated(ID)), this, SLOT(addItem(ID)));
}

void AnalysisWindow::addItem(const ID &item)
{
    if(!analyzesModel_->containsPointList(item))
    {
        analyzesModel_->appendPointList(item);
    }
    else
    {
        qWarning() << QString("PointList with id:{%1} already in the table for analysis").arg(item);
    }
}
