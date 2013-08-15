#ifndef TESTINGUTILITIES_H

#define TESTINGUTILITIES_H

#include <QTest>

#include "../src/AbstractAnalysis.h"
#include "../src/AnalysisCollection.h"

#define FUZZY_COMPARE(a, b) if(!(qAbs(a - b) < 0.0001)) QFAIL(QString("Compared values are not the same\nActual: %1\nExpected: %2").arg(a).arg(b).toStdString().c_str())
#define FUZZY_COMPARE_EPS(a, b, eps) if(!(qAbs(a - b) < eps)) QFAIL(QString("Compared values are not the same(eps = %1)\nActual: %2\nExpected: %3").arg(eps).arg(a).arg(b).toStdString().c_str())

extern QString sequencePointListToString(const SequencePointList &spl);
extern QString pointListToString(const PointList &pl);
extern bool pointListFuzzyCompare(const PointList& actual, const PointList& expected);
extern bool seqPointListFuzzyCompare(const SequencePointList& actual, const SequencePointList& expected);

extern QString analysisResultsToString(const AnalysisResults analysisResults);
extern QString analysisResultToString(const AnalysisResult analysisResult);
extern bool analysisResultFuzzyCompare(const AnalysisResult& actual, const AnalysisResult& expected);
extern bool analysisResultsFuzzyCompare(const AnalysisResults& actual, const AnalysisResults& expected);

extern bool fuzzyCompare(const double actual, const double expected);

#endif // TESTINGUTILITIES_H
