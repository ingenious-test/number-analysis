#ifndef CSVPOINTLISTVALIDATOR_H

#define CSVPOINTLISTVALIDATOR_H

#include "AbstractAnalysis.h"

class CSVPointListValidator
{
public:
    struct Error{
        Error()
            : line(0), errorStr(QString()) {}

        int line;
        QString errorStr;
    };

    CSVPointListValidator();

    bool validation(const QString& fileName);
    const Error& lastError();


 private:
    void error(const QString& errorStr, const QString& fileName, const int line);
    Error lastError_;
};

#endif // CSVPOINTLISTVALIDATOR_H
