#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    analyzesView_ = new QTableView();
    analyzesModel_ = new AnalysisTableModel();

    analyzesView_->setModel(analyzesModel_);

    setCentralWidget(analyzesView_);
}

MainWindow::~MainWindow()
{
    
}
