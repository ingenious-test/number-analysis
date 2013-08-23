#include "CSVPointListValidator.h"

CSVPointListValidator::CSVPointListValidator()
{
}

bool CSVPointListValidator::validation(const QString &fileName)
{
    if(!QFile::exists(fileName))
    {
        qWarning() << fileName << " do not exists";
        return false;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << fileName << " not open";
        return false;
    }

    if(file.size() == 0)
    {
        qWarning() << "file is empty";
        return true;
    }

    int lineNum = 0;
    while(!file.atEnd())
    {
        lineNum++;
        QString lineData = file.readLine();
        QStringList valueList = lineData.split(";");

        if(valueList.count() != 2)
        {
            errorMSG("values count must be two", fileName, lineNum);
            return false;
        }

        ID id = valueList.at(0);
        if(id.isNull())
        {
            errorMSG("id not set", fileName, lineNum);
            return false;
        }

        bool isOk = false;
        valueList.at(1).toDouble(&isOk);

        if(!isOk)
        {
            errorMSG("point value is not double", fileName, lineNum);
            return false;
        }

    }

    return true;
}

void CSVPointListValidator::errorMSG(const QString &errorStr, const QString &fileName, const int line)
{
    qWarning()
            << errorStr.toStdString().c_str()
            << "in file " << fileName.toStdString().c_str()
            << "in line " << line;
}
