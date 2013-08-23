#ifndef CSVPOINTLISTVALIDATOR_H

#define CSVPOINTLISTVALIDATOR_H

#include "AbstractAnalysis.h"

class CSVPointListValidator
{

public:
    CSVPointListValidator();

    static bool validation(const QString& fileName);
 private:
    static void errorMSG(const QString& errorStr, const QString& fileName, const int line);
};

#endif // CSVPOINTLISTVALIDATOR_H
