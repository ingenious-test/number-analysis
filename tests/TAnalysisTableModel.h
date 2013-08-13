#ifndef TANALYSISTABLEMODEL_H

#define TANALYSISTABLEMODEL_H

#include <QTest>

#include "../src/AnalysisCollection.h"
#include "../src/StupidAnalysis.h"
#include "../src/AverageAnalysis.h"
#include "../src/AnalysisTableModel.h"


class TAnalysisTableModel : public QObject
{
    Q_OBJECT
public:
    TAnalysisTableModel();


private slots:
    void TestAddRemoveMoc_data();
    void TestAddRemoveMoc();
};

#endif // TANALYSISTABLEMODEL_H
