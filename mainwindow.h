#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QTableView>
#include <QtGui/QLayout>

#include "src/AnalysisTableModel.h"
#include "src/StupidAnalysis.h"
#include "src/AverageAnalysis.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTableView* analyzesView_;
    AnalysisTableModel* analyzesModel_;

};

#endif // MAINWINDOW_H
