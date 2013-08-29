#include "AnalysisWindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent) :
    QWidget(parent),
    dataBaseName_("database.db"),
    tableName_("points")
{
   /* if(QFile::exists(dataBaseName_))
    {
        if(!QFile::remove(dataBaseName_))
        {
            qWarning() << "can't remove testing database";
        }
    }

    SqlPointListWriter writer(dataBaseName_, tableName_);
    writer.open();
    SequencePointList seq;
    for(int i = 0; i < 1500; i++)
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
    qWarning() << "------END-WRITE-------";*/

    DatabaseGenerator databaseGenerator;

    databaseGenerator.generateDataBase(dataBaseName_,tableName_);

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
    prevAnalysisPageButton_ = new QToolButton;
    prevAnalysisPageButton_->setArrowType(Qt::LeftArrow);
    analysisPageLabel_ = new QLabel("0/0");
    nextAnalysisPageButton_ = new QToolButton;
    nextAnalysisPageButton_->setArrowType(Qt::RightArrow);

    analysisButtonsSection->addWidget(prevAnalysisPageButton_);
    analysisButtonsSection->addWidget(analysisPageLabel_);
    analysisButtonsSection->addWidget(nextAnalysisPageButton_);
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


    connect(seqPointListModel_, SIGNAL(dataChanged()), this, SLOT(onSeqModelDataChanged()));
    connect(seqPointListView_->scroll(), SIGNAL(valueChanged(int)), this, SLOT(onSeqViewScrollValueChanged(int)));
    connect(seqPointListView_, SIGNAL(listResized()), this, SLOT(onSeqViewResized()));
    connect(seqPointListModel_, SIGNAL(itemsCountOnPageChanged()), this, SLOT(onSeqModelItemOnPagesChanged()));



    connect(analyzesModel_, SIGNAL(currentPageChanged()), this, SLOT(onChangeAnalysisPage()));
    connect(analyzesModel_, SIGNAL(itemsCountOnPageChanged()), this, SLOT(onChangeAnalysisPage()));
    connect(analyzesModel_, SIGNAL(dataChanged()), this, SLOT(onChangeAnalysisPage()));
    connect(prevAnalysisPageButton_, SIGNAL(clicked()), this, SLOT(onPrevAnalysisPageButtonClick()));
    connect(nextAnalysisPageButton_, SIGNAL(clicked()), this, SLOT(onNextAnalysisPageButtonClick()));


    analyzesModel_->setItemsCountOnPage(5);
    analyzesModel_->setCurrentPage(0);

    seqPointListModel_->setStartOutItem(0);
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

void AnalysisWindow::onSeqModelDataChanged()
{
    seqPointListView_->scroll()->setRange(0, seqPointListModel_->lastStartOutItem());
    seqPointListView_->scroll()->setToolTip(QString::number(seqPointListModel_->startOutItem())
                                            + "/"
                                            + QString::number(seqPointListModel_->lastStartOutItem()));
}

void AnalysisWindow::onSeqViewScrollValueChanged(int value)
{
    const QModelIndex index = seqPointListView_->currentIndex();
    seqPointListModel_->setStartOutItem(value);
    seqPointListView_->setCurrentIndex(index);
    seqPointListView_->scroll()->setToolTip(QString::number(seqPointListModel_->startOutItem())
                                            + "/"
                                            + QString::number(seqPointListModel_->lastStartOutItem()));
}

void AnalysisWindow::onSeqViewResized()
{
    const QModelIndex index = seqPointListView_->currentIndex();

    QFontMetrics metrics(seqPointListView_->font());
    seqPointListModel_->setOutItemsCount(((seqPointListView_->height()) / (metrics.height() + 2)));
    seqPointListView_->scroll()->setRange(0, seqPointListModel_->lastStartOutItem());
    seqPointListView_->scroll()->setValue(seqPointListModel_->startOutItem());

    seqPointListView_->setCurrentIndex(index);
}

void AnalysisWindow::onSeqModelItemOnPagesChanged()
{
    seqPointListView_->scroll()->setRange(0, seqPointListModel_->lastStartOutItem());
    seqPointListView_->scroll()->setToolTip(QString::number(seqPointListModel_->startOutItem())
                                            + "/"
                                            + QString::number(seqPointListModel_->lastStartOutItem()));
}


void AnalysisWindow::onPrevAnalysisPageButtonClick()
{
    if(analyzesModel_->currentPage() != 0)
    {
        analyzesModel_->setCurrentPage(analyzesModel_->currentPage() - 1);
    }
}

void AnalysisWindow::onNextAnalysisPageButtonClick()
{
    if(analyzesModel_->currentPage() + 1 != analyzesModel_->pagesCount())
    {
        analyzesModel_->setCurrentPage(analyzesModel_->currentPage() + 1);
    }
}

void AnalysisWindow::onChangeAnalysisPage()
{
    prevAnalysisPageButton_->setVisible(analyzesModel_->pagesCount() > 1);
    nextAnalysisPageButton_->setVisible(analyzesModel_->pagesCount() > 1);
    analysisPageLabel_->setVisible(analyzesModel_->pagesCount() > 1);


    prevAnalysisPageButton_->setEnabled(analyzesModel_->currentPage() != 0);
    nextAnalysisPageButton_->setEnabled(analyzesModel_->currentPage() + 1 != analyzesModel_->pagesCount());

    const QString pageLabelText = QString::number(analyzesModel_->currentPage() + 1) + "/" + QString::number(analyzesModel_->pagesCount());
    analysisPageLabel_->setText(pageLabelText);
}
