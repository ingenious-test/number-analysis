#include "TCSVPointListValidator.h"

TCSVPointListValidator::TCSVPointListValidator()
{
}

void TCSVPointListValidator::TestValidation_data()
{
    QTest::addColumn<QStringList>("data");
    QTest::addColumn<bool>("isValid");

    QTest::newRow("empty") << QStringList() << true;

    QTest::newRow("correct-single-line-data")
            << (QStringList()
                << QString("id1;0.55"))
            << true;

    QTest::newRow("incorrect-single-line-data")
            << (QStringList()
                << QString("id1;0."))
            << false;

    QTest::newRow("incorrect-single-line-data1")
            << (QStringList()
                << QString("id1;.0"))
            << false;

    QTest::newRow("incorrect-single-line-data2")
            << (QStringList()
                << QString("id1;                  123"))
            << false;

    QTest::newRow("correct-two-lines-data")
            << (QStringList()
                << QString("id1;0.55")
                << QString("id1;0.35"))
            << true;

    QTest::newRow("incorrect-two-lines--data")
            << (QStringList()
                << QString("id1;0.55")
                << QString("asdasdasdasdasd;asdasd;asdasd;asdasddasdsf7b5nghjl74hgb8n97"))
            << false;

    QTest::newRow("correct-three-lines-data")
            << (QStringList()
                << QString("id1;0.55")
                << QString("id1;0.35")
                << QString("id2;0.33")
                )
            << true;

    QTest::newRow("incorrect-three-lines--data")
            << (QStringList()
                << QString("id1;0.55")
                << QString("id1;1.e-19")
                << QString("id2;0.33"))
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
    if(!sourceFile.open(QFile::WriteOnly | QIODevice::Text))
    {
        QFAIL("can't open testing source file for writing");
    }
    QTextStream sourceFileStream(&sourceFile);
    sourceFileStream << data.join("\n");
    sourceFile.flush();
    sourceFile.close();

    CSVPointListValidator csvValidator;

    const bool actualResult = csvValidator.validation(sourceFileName);
    const bool expectedResult = isValid;

    if(!actualResult)
    {
        qWarning() << csvValidator.lastError().errorStr << "in line" << csvValidator.lastError().line;
    }

    QCOMPARE(actualResult, expectedResult);
}

void TCSVPointListValidator::TestRegExp_data()
{
    QTest::addColumn<QString>("testStr");
    QTest::addColumn<bool>("result");


    QTest::newRow("first-incorrect")  << "id1;0." << false;
    QTest::newRow("second-incorrect")  << "id1;.0" << false;
    QTest::newRow("third-incorrect")  << "id1;         123123" << false;
    QTest::newRow("fifth-incorrect")  << "id1;1.e-19" << false;
    QTest::newRow("six-incorrect") << "id4;1.0e-19" << false;

    QTest::newRow("first-correct") << "id1;0.0" << true;
    QTest::newRow("second-correct") << "id2;-1.0" << true;
    QTest::newRow("third-correct") << "id3;123123" << true;

}

void TCSVPointListValidator::TestRegExp()
{
    QFETCH(QString, testStr);
    QFETCH(bool, result);

    QRegExp regexpr("^\\w+;-?\\d+(.\\d+)?$");


    const bool actualResult = regexpr.exactMatch(testStr);
    const bool expectedResult = result;

    QCOMPARE(actualResult, expectedResult);
}
