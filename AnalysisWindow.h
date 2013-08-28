#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QTableView>
#include <QtGui/QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QFileDialog>
#include <QToolButton>
#include <QLabel>

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
#include "src/CSVPointListImporter.h"
#include "src/CSVPointListExporter.h"

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

    const QString dataBaseName_;
    const QString tableName_;

    QToolButton* prevSeqPageButton_;
    QLabel* seqPageLabel_;
    QToolButton* nextSeqPageButton_;

    QToolButton* prevAnalysisPageButton_;
    QLabel* analysisPageLabel_;
    QToolButton* nextAnalysisPageButton_;


    void createMenu();

private slots:
    void addItem(const ID &item);
    void addItems(const IDList &items);

    void onAnalyzeButtonClick();
    void onStatisticsClick();

    void onExportClick();
    void onImportClick();

    void onPrevSeqPageButtonClick();
    void onNextSeqPageButtonClick();
    void onChangeSeqPage();

    void onPrevAnalysisPageButtonClick();
    void onNextAnalysisPageButtonClick();
    void onChangeAnalysisPage();
};

#endif // WIDGET_H
