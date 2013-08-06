#ifndef TANALYSISCOLLECTION_H

#define TANALYSISCOLLECTION_H

#include <QTest>

#include "../src/AnalysisCollection.h"
#include "../src/StupidAnalysis.h"

class TAnalysisCollection : public QObject
{
    Q_OBJECT
public:
    TAnalysisCollection();

private slots:
    void TestAnalyzeAnalysis_data();
    void TestAnalyzeAnalysis(); //анализируем
};

#endif // TANALYSISCOLLECTION_H
