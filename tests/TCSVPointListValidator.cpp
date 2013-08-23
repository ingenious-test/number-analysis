#include "TCSVPointListValidator.h"

TCSVPointListValidator::TCSVPointListValidator()
{
}

void TCSVPointListValidator::TestValidation_data()
{
    QTest::addColumn<QStringList>("data");
    QTest::addColumn<bool>("isValid");

    QTest::newRow("empty") << QStringList() << true;

    QTest::newRow("correct-data")
            << (QStringList()
                << QString("id1;0.55")
                << QString("id1;0.35"))
            << true;

    QTest::newRow("incorrect-data")
            << (QStringList()
                << QString("id1;0.55")
                << QString("asdasdasdasdasd;asdasd;asdasd;asdasddasdsf7b5nghjl74hgb8n97")
                << QString("asdasdasdasdasd;asdasd;asdasd;asdasddasdsf7b5nghjl74hgb8n97"))
            << false;
}

void TCSVPointListValidator::TestValidation()
{
    QFETCH(QStringList, data);
    QFETCH(bool, isValid);

    const QString sourceFileName = QString(QTest::currentDataTag()) + QTest::currentTestFunction() + ".csv";

    if(QFile::exists(sourceFileName))
    {
        if(!QFile::remove(sourceFileName))
        {
            QFAIL("can't remove testing source file");
        }
    }

    QFile sourceFile(sourceFileName);
    if(!sourceFile.open(QFile::WriteOnly))
    {
        QFAIL("can't open testing source file for writing");
    }
    QTextStream sourceFileStream(&sourceFile);
    sourceFileStream << data.join("\n");
    sourceFile.flush();
    sourceFile.close();

    const bool actualResult = CSVPointListValidator::validation(sourceFileName);
    const bool expectedResult = isValid;

    QCOMPARE(actualResult, expectedResult);
}
