#ifndef TESTINGUTILITIES_H

#define TESTINGUTILITIES_H

#include <QTest>

#define FUZZY_COMPARE(a, b) if(qAbs(a - b) < 0.0001) QVERIFY(true); else QVERIFY2(false, "non-fuzzy-equal doubles")
#define FUZZY_COMPARE_EPS(a, b, eps) if(qAbs(a - b) < eps) QVERIFY(true); else QVERIFY2(false, "non-fuzzy-equal doubles")

#endif // TESTINGUTILITIES_H
