#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    analyzesView_ = new QTableView();
    AnalysisList list;
    list.insertInc(new StupidAnalysis(1.0))
            .insertInc(new AverageAnalysis);
    analyzesModel_ = new AnalysisTableModel(
                AnalysisCollection(list),
                (SequencePointList() << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0)));

    analyzesModel_->analyze();

    analyzesView_->setModel(analyzesModel_);

    setCentralWidget(analyzesView_);
}

MainWindow::~MainWindow()
{
    
}
