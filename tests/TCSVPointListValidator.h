#ifndef TCSVPOINTLISTVALIDATOR_H

#define TCSVPOINTLISTVALIDATOR_H

#include <QTest>
#include <QTextStream>

#include "../src/CSVPointListValidator.h"

class TCSVPointListValidator : public QObject
{
    Q_OBJECT
public:
    TCSVPointListValidator();

private slots:
    void TestValidation_data();
    void TestValidation();

    void TestRegExp_data();
    void TestRegExp();
};

#endif // TCSVPOINTLISTVALIDATOR_H
