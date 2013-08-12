#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QTableView>
#include <QtGui/QLayout>

#include "src/ItemListView.h"

#include "src/AnalysisTableModel.h"
#include "src/ItemListModel.h"
#include "src/StupidAnalysis.h"
#include "src/AverageAnalysis.h"
#include "src/AverageIgnoreNullAnalysis.h"

class AnalysisWindow : public QWidget
{
    Q_OBJECT
    
public:
    AnalysisWindow(QWidget *parent = 0);
    ~AnalysisWindow();

private:
    QTableView* analyzesView_;
    AnalysisTableModel* analyzesModel_;

    ItemListView* seqPointListView_;
    ItemListModel* seqPointListModel_;

private slots:
    void addItem(const ID &item);


};

#endif // WIDGET_H
