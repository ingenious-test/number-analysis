#ifndef TCSVPOINTLISTIMPORTER_H

#define TCSVPOINTLISTIMPORTER_H

#include "QtTest"

#include "../src/Metatypes.h"

class TCSVPointListImporter : public QObject
{
    Q_OBJECT
public:
    TCSVPointListImporter();

private slots:
    void TestImport_data();
    void TestImport();
};

#endif // TCSVPOINTLISTIMPORTER_H
