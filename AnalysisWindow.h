#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QTableView>
#include <QtGui/QLayout>
#include <QPushButton>
#include <QMenuBar>

#include "src/ItemListView.h"

#include "src/AnalysisTableModel.h"
#include "src/ItemListModel.h"
#include "src/StupidAnalysis.h"
#include "src/AverageAnalysis.h"
#include "src/AverageIgnoreNullAnalysis.h"
#include "src/SqlPointListReader.h"
#include "src/SqlPointListWriter.h"
#include "src/DatabaseGenerator.h"
#include "src/PointListStorageStatisticsDialog.h"

class AnalysisWindow : public QWidget
{
    Q_OBJECT
    
public:
    AnalysisWindow(QWidget *parent = 0);
    ~AnalysisWindow();

private:
    QPushButton* analyzeButton;

    QTableView* analyzesView_;
    AnalysisTableModel* analyzesModel_;

    ItemListView* seqPointListView_;
    ItemListModel* seqPointListModel_;

    AbstractPointListReader *reader_;

    QMenuBar* mainMenu_;


    void createMenu();

private slots:
    void addItem(const ID &item);
    void onAnalyzeButtonClick();
    void onStatisticsClick();
};

#endif // WIDGET_H
