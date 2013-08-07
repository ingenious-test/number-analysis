#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    analyzesView_ = new QTableView();
    analyzesModel_ = new AnalysisTableModel(
                new AnalysisCollection(AnalysisList()
                                       << new StupidAnalysis(1.0) << new AverageAnalysis()),
                (SequencePointList() << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0)));

    analyzesModel_->analyze();

    analyzesView_->setModel(analyzesModel_);

    setCentralWidget(analyzesView_);
}

MainWindow::~MainWindow()
{
    
}
