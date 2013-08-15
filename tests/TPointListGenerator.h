#ifndef TPOINTLISTGENERATOR_H

#define TPOINTLISTGENERATOR_H

#include <QTest>

#include "TestingUtilities.h"

#include "../src/PointListGenerator.h"

class TPointListGenerator : public QObject
{
    Q_OBJECT

public:
    TPointListGenerator(QObject *parent = 0);

private slots:
    void TestGenerator_data();
    void TestGenerator();
};

#endif // TPOINTLISTGENERATOR_H
