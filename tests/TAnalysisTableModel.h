#ifndef TANALYSISTABLEMODEL_H

#define TANALYSISTABLEMODEL_H

#include <QTest>

#include "TestingUtilities.h"

#include "../src/AnalysisCollection.h"
#include "../src/StupidAnalysis.h"
#include "../src/AverageAnalysis.h"
#include "../src/AnalysisTableModel.h"
#include "../src/SqlPointListReader.h"
#include "../src/SqlPointListWriter.h"


class TAnalysisTableModel : public QObject
{
    Q_OBJECT
public:
    TAnalysisTableModel();


private slots:
    void TestAddRemoveMoc_data();
    void TestAddRemoveMoc();

    void TestAddRemoveSql_data();
    void TestAddRemoveSql();
};

#endif // TANALYSISTABLEMODEL_H
