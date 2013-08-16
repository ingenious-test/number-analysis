#ifndef TPOINTLISTGENERATOR_H

#define TPOINTLISTGENERATOR_H

#include <QTest>

#include "TestingUtilities.h"

#include "../src/PointListGenerator.h"

#include "../src/Metatypes.h"

class TPointListGenerator : public QObject
{
    Q_OBJECT

public:
    TPointListGenerator(QObject *parent = 0);

private slots:
    void TestGenerator_data();
    void TestGenerator();

    void TestValueGenerator_data();
    void TestValueGenerator();

    void TestStartEndGenerator_data();
    void TestStartEndGenerator();
};

#endif // TPOINTLISTGENERATOR_H
