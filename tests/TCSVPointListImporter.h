#ifndef TCSVPOINTLISTIMPORTER_H

#define TCSVPOINTLISTIMPORTER_H

#include <QTest>

#include "../src/Metatypes.h"
#include "../src/CSVPointListImporter.h"
#include "../src/SqlPointListReader.h"

class TCSVPointListImporter : public QObject
{
    Q_OBJECT
public:
    TCSVPointListImporter();

private slots:
    void TestParseLine_data();
    void TestParseLine();

    void TestImportPointList_data();
    void TestImportPointList();


};

#endif // TCSVPOINTLISTIMPORTER_H
