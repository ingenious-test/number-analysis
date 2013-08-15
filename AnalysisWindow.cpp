#include "AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent)
    : QWidget(parent),
      reader_(new SqlPointListReader("database.db", "points"))
{
    SqlPointListWriter writer("database.db", "points");
    if(writer.isOpen())
    {
        writer.write(ID("id2"), PointList() << 1.0 << 2.0);
        writer.write(ID("id1"), PointList() << -1.0 << 0.0001);
        writer.write(ID("ид3"), PointList() << 0.0 << 42.0 << 0.0);
        writer.write(ID("ид2"), PointList() << 0.0 << 42.0 << 0.0);
        writer.write(ID("ид1"), PointList() << 0.0 << 42.0 << 0.0);
        writer.write(ID("ид0"), PointList() << 0.0 << 42.0 << 0.0);
    }


    QHBoxLayout* mainLayout = new QHBoxLayout;

    AnalysisList analyzes;
    analyzes << new StupidAnalysis(1.0)
             << new AverageIgnoreNullAnalysis()
             << new AverageAnalysis;

    analyzesModel_ = new AnalysisTableModel(reader_);

    foreach(AbstractAnalysis* analysis, analyzes)
    {
        analyzesModel_->addAnalysis(analysis);
        delete analysis;
    }

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
    delete reader_;
    SqlPointListInterface::removeConnection();
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
