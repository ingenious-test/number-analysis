#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    analyzesView_ = new QTableView();
    AnalysisList list;
    list
            .insertInc(new StupidAnalysis(1.0))
            .insertInc(new AverageIgnoreNullAnalysis())
            .insertInc(new AverageAnalysis)
            ;
    analyzesModel_ = new AnalysisTableModel(
                AnalysisCollection(list),
                SequencePointList()
                .appendInc("Первый",
                           PointList()
                           .appendInc(2.0)
                           .appendInc(3.0))
                .appendInc("Второй",
                           PointList()
                            .appendInc(1.0)
                            .appendInc(2.0)
                            .appendInc(0.0 )
                            .appendInc(4.0)));


    analyzesModel_->analyze();

    analyzesView_->setModel(analyzesModel_);
    ;


    setCentralWidget(analyzesView_);
}

MainWindow::~MainWindow()
{

}
