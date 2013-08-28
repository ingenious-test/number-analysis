#include "CSVPointListValidator.h"

CSVPointListValidator::CSVPointListValidator()
{
}

bool CSVPointListValidator::validation(const QString &fileName)
{
    lastError_ = Error();

    if(!QFile::exists(fileName))
    {
        lastError_.errorStr = fileName + " do not exists";
        return false;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        lastError_.errorStr = fileName + " not open";
        return false;
    }

    if(file.size() == 0)
    {
        qWarning() << fileName << "file is empty";
        return true;
    }

    int lineNum = 0;
    while(!file.atEnd())
    {
        lineNum++;
        QString lineData = file.readLine();
        if(!lineData.isEmpty())
        {
            const int lastInd = lineData.count() - 1;
            if(lineData.at(lastInd) == '\n')
            {
                lineData.remove(lastInd,1);
            }
        }

        const QString regExprStr = QString("^\\w.+;-?\\d+(.\\d+)?$");
        const QRegExp regExpr(regExprStr);

        const bool isMatch = regExpr.exactMatch(lineData);

        if(!isMatch)
        {
            error("not math to regexp " + regExprStr, fileName, lineNum);
            file.flush();
            file.close();
            return false;
        }

    }

    file.flush();
    file.close();
    return true;
}

const CSVPointListValidator::Error &CSVPointListValidator::lastError()
{
    return lastError_;
}

void CSVPointListValidator::error(const QString &errorStr, const QString &fileName, const int line)
{
    lastError_.errorStr = errorStr + " in file " + fileName;
    lastError_.line = line;
}
