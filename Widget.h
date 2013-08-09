#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QTableView>
#include <QtGui/QListView>
#include <QtGui/QLayout>

#include "src/AnalysisTableModel.h"
#include "src/ItemListModel.h"
#include "src/StupidAnalysis.h"
#include "src/AverageAnalysis.h"
#include "src/AverageIgnoreNullAnalysis.h"

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QTableView* analyzesView_;
    AnalysisTableModel* analyzesModel_;

    QListView* seqPointListView_;
    ItemListModel* seqPointListModel_;

private slots:
    void	pointsListDoubleCLicked(QModelIndex index);


};

#endif // WIDGET_H
