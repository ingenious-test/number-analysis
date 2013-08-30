#include "AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent) :
    QWidget(parent),
    dataBaseName_("database.db"),
    tableName_("points")
{
    if(QFile::exists(dataBaseName_))
    {
        if(!QFile::remove(dataBaseName_))
        {
            qWarning() << "can't remove testing database";
        }
    }

    SqlPointListWriter writer(dataBaseName_, tableName_);
    writer.open();
    SequencePointList seq;
    for(int i = 0; i < 100000; i++)
    {
        qDebug() << i;
        PointList pointList(QString("id%1").arg(i));
        for(int j = 0; j < 1; j++)
        {
            pointList << Point(j);
  }
        seq.append(pointList);
    }

    qWarning() << "------BEGIN-WRITE-------";
    writer.write(seq);
    qWarning() << "------END-WRITE-------";

//    DatabaseGenerator databaseGenerator;

//    databaseGenerator.generateDataBase(dataBaseName_,tableName_);

    reader_ = new SqlPointListReader(dataBaseName_, tableName_);
    static_cast<SqlPointListReader*>(reader_)->open();

    StatisticsList statisticsList;
    statisticsList << new MaxSequenceLengthIdStatistics
                   << new MaxSequenceLengthStatistics
                   << new FiveTopSequenceLengthStatistics
                   << new MinSequenceLengthIdStatistics
                   << new MinSequenceLengthStatistics
                   << new AverageSequenceLengthStatistics
                   << new AverageNullCountPointsStatistics
                   << new AverageNoneNullCountPointsStatistics
                   << new PercentNullCountPointsStatistics
                   << new PercentNoneNullCountPointsStatistics
                   << new MaxPointStatistics
                   << new MinPointStatistics
                   << new FiveTopPointsValueStatistics
                   << new SequenceWithRepeatCountStatistics
                   << new IncSequenceCountStatistics
                   << new DecSequenceCountStatistics;

    static_cast<SqlPointListReader*>(reader_)->appendStatistics(statisticsList);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* subLayout = new QHBoxLayout;

    AnalysisList analyzes;
    analyzes << new StupidAnalysis(1.0)
             << new AverageIgnoreNullAnalysis()
             << new AverageAnalysis;

    this->createMenu();

    analyzesModel_ = new AnalysisTableModel(reader_);

    foreach(AbstractAnalysis* analysis, analyzes)
    {
        analyzesModel_->addAnalysis(analysis);
        delete analysis;
    }

    analyzesView_ = new QTableView();
    analyzesView_->setSortingEnabled(true);

    analyzesView_->setModel(analyzesModel_);

    seqPointListModel_ = new ItemListModel(reader_);

    seqPointListView_ = new ItemListView();
    seqPointListView_->setFixedWidth(300);
    seqPointListView_->setModel(seqPointListModel_);

    analyzeButton = new QPushButton("Провести анализ");


    QHBoxLayout* analysisButtonsSection = new QHBoxLayout;
    analysisButtonsSection->addStretch();
    analysisButtonsSection->addWidget(analyzeButton);

    QVBoxLayout* analyzesResultSectionLayout = new QVBoxLayout;
    analyzesResultSectionLayout->addWidget(analyzesView_);
    analyzesResultSectionLayout->addLayout(analysisButtonsSection);

    subLayout->addWidget(seqPointListView_);
    subLayout->addLayout(analyzesResultSectionLayout);

    mainLayout->addWidget(mainMenu_);
    mainLayout->addLayout(subLayout);

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    subLayout->setMargin(5);
    subLayout->setSpacing(5);

    subLayout->setStretch(0,0);
    subLayout->setStretch(1,1);

    setLayout(mainLayout);

    connect(seqPointListView_, SIGNAL(itemActivated(ID)), this, SLOT(addItem(ID)));
    connect(seqPointListView_, SIGNAL(itemsActivated(IDList)), this, SLOT(addItems(IDList)));
    connect(analyzeButton, SIGNAL(clicked()), this, SLOT(onAnalyzeButtonClick()));
}

AnalysisWindow::~AnalysisWindow()
{
    delete reader_;
    SqlPointListInterface::removeConnection();
}

void AnalysisWindow::createMenu()
{
    mainMenu_ = new QMenuBar;

    mainMenu_->addAction("Статисткика", this, SLOT(onStatisticsClick()));


    QMenu* menuData = mainMenu_->addMenu("Данные");
    menuData->addAction("Импорт", this, SLOT(onImportClick()));
    menuData->addAction("Экспорт", this, SLOT(onExportClick()));
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

void AnalysisWindow::addItems(const IDList &items)
{
    foreach(const ID& item, items)
    {
        addItem(item);
    }
}

void AnalysisWindow::onAnalyzeButtonClick()
{
    analyzesModel_->analyzeAll();
}

void AnalysisWindow::onStatisticsClick()
{
    PointListStorageStatisticsDialog dialog(reader_->statistics());
    dialog.exec();
}

void AnalysisWindow::onExportClick()
{
    QString exportFileName = QFileDialog::getSaveFileName(this, QString("Export File"),
                                QDir::currentPath(),
                                QString("CSV (*.csv)"));
    if(!exportFileName.isEmpty())
    {
        CSVPointListExporter csvExporter(dataBaseName_, tableName_, exportFileName);
        csvExporter.exportFromDataBase();
    }
}

void AnalysisWindow::onImportClick()
{
    QString importFileName = QFileDialog::getOpenFileName(this, QString("Import File"),
                                                    QDir::currentPath(),
                                                    QString("CSV (*.csv)"));
    if(!importFileName.isEmpty())
    {
        CSVPointListImporter csvImporter(importFileName, dataBaseName_, tableName_);
        if(!csvImporter.import())
        {
            qWarning() << importFileName << "not imported";
            return;
        }
        seqPointListModel_->update();
    }
}
