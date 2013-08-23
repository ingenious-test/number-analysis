#ifndef TCSVPOINTLISTEXPORTER_H

#define TCSVPOINTLISTEXPORTER_H

#include <QTest>

#include "../src/Metatypes.h"
#include "../src/SqlPointListWriter.h"
#include "../src/CSVPointListExporter.h"

class TCSVPointListExporter : public QObject
{
    Q_OBJECT
public:
    TCSVPointListExporter();

private slots:
    void TestExportPointList_data();
    void TestExportPointList();
};

#endif // TCSVPOINTLISTEXPORTER_H
