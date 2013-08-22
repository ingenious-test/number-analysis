#ifndef TESTINGUTILITIES_H

#define TESTINGUTILITIES_H

#include <QTest>

#include "../src/AbstractAnalysis.h"
#include "../src/AnalysisCollection.h"

#define FUZZY_COMPARE(a, b) if(!(qAbs(a - b) < 0.0001)) QFAIL(QString("Compared values are not the same\nActual: %1\nExpected: %2").arg(a).arg(b).toStdString().c_str())
#define FUZZY_COMPARE_EPS(a, b, eps) if(!(qAbs(a - b) < eps)) QFAIL(QString("Compared values are not the same(eps = %1)\nActual: %2\nExpected: %3").arg(eps).arg(a).arg(b).toStdString().c_str())

#endif // TESTINGUTILITIES_H
