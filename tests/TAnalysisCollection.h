#ifndef TANALYSISCOLLECTION_H

#define TANALYSISCOLLECTION_H

#include <QTest>

#include "../src/AnalysisCollection.h"
#include "../src/StupidAnalysis.h"
#include "../src/AverageAnalysis.h"
#include "../src/AverageIgnoreNullAnalysis.h"

class TAnalysisCollection : public QObject
{
    Q_OBJECT
public:
    TAnalysisCollection();

private slots:
    void TestAnalyzeAnalysis_data();
    void TestAnalyzeAnalysis();

    void TestAnalyzeAnalysisAddRemove_data();
    void TestAnalyzeAnalysisAddRemove();

};

#endif // TANALYSISCOLLECTION_H
