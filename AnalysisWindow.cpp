#include "AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent)
    : QWidget(parent)
{
    DatabaseGenerator databaseGenerator;

    databaseGenerator.generateDataBase("database.db", "points");

    reader_ = new SqlPointListReader("database.db", "points");

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

    analyzeButton = new QPushButton("Провести анализ");




    QHBoxLayout* subLayout_1 = new QHBoxLayout;
    subLayout_1->addStretch();
    subLayout_1->addWidget(analyzeButton);

    QVBoxLayout* subLayout = new QVBoxLayout;
    subLayout->addWidget(analyzesView_);
    subLayout->addLayout(subLayout_1);


    mainLayout->addWidget(seqPointListView_);
    mainLayout->addLayout(subLayout);


    setLayout(mainLayout);

    connect(seqPointListView_, SIGNAL(itemActivated(ID)), this, SLOT(addItem(ID)));
    connect(analyzeButton, SIGNAL(clicked()), this, SLOT(onAnalyzeButtonClick()));
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

void AnalysisWindow::onAnalyzeButtonClick()
{
    analyzesModel_->analyzeAll();
}
