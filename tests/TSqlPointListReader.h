#ifndef TSQLPOINTLISTREADER_H

#define TSQLPOINTLISTREADER_H

#include "QtTest"

#include "../src/SqlPointListReader.h"
#include "../src/SqlPointListWriter.h"

class TSqlPointListReader : public QObject
{
    Q_OBJECT

public:
    TSqlPointListReader();

private slots:
    void TestWriteRead_data();
    void TestWriteRead();
};

#endif // TSQLPOINTLISTREADER_H
