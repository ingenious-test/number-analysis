#include "AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent)
    : QWidget(parent),
      reader_(new SqlPointListReader("database.db"))
{
    SqlPointListWriter writer("database.db");
    writer.write(ID("id1"), PointList() << 1.0 << 2.0);
    writer.write(ID("id2"), PointList() << -1.0 << 0.0001);
    writer.write(ID("ид3"), PointList() << 0.0 << 42.0 << 0.0);

    QHBoxLayout* mainLayout = new QHBoxLayout;

    AnalysisList list;
    list << new StupidAnalysis(1.0)
         << new AverageIgnoreNullAnalysis()
         << new AverageAnalysis;

    analyzesModel_ = new AnalysisTableModel(list);

    analyzesView_ = new QTableView();

    analyzesView_->setModel(analyzesModel_);

    seqPointListModel_ = new ItemListModel(reader_);

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
