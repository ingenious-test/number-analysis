#ifndef POINTLISTSTORAGESTATISTICSDIALOG_H

#define POINTLISTSTORAGESTATISTICSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>

#include "PointListStorageStatistics.h"

class PointListStorageStatisticsDialog : public QDialog
{
    Q_OBJECT
public:
    PointListStorageStatisticsDialog(PointListStorageStatistics &statistics, QWidget *parent = 0);

private:
    QTextEdit* text_;
    QPushButton* okButton_;
        
};

#endif // POINTLISTSTORAGESTATISTICSDIALOG_H
