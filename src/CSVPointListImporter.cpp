#include "CSVPointListImporter.h"


CSVPointListImporter::CSVPointListImporter(const QString &sourceFileName,
                                           const QString &targetFileName,
                                           const QString &targetTableName) :
    sourceFileName_(sourceFileName),
    targetFileName_(targetFileName),
    targetTableName_(targetTableName)

{
}

void CSVPointListImporter::import()
{
    QFile file(sourceFileName_);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "csv not open";
        return;
    }

    SequencePointList sequencePoint;
    PointList tempPointList;
    QString lastID;

    while (!file.atEnd())
    {
        QString line = file.readLine();
        ParsedPoint parsedLine = parseLine(line);

        if(lastID.isNull())
        {
            lastID = parsedLine.id;
        }

        if((lastID != parsedLine.id) || file.atEnd())
        {
            tempPointList.append(parsedLine.value);
            if(!sequencePoint.contains(lastID))
            {
                tempPointList.setID(lastID);
                sequencePoint.append(tempPointList);
            }

            tempPointList.clear();
        }
        else
        {
           tempPointList.append(parsedLine.value);
        }


        lastID = parsedLine.id;
    }

    file.flush();
    file.close();

    SqlPointListWriter writer(targetFileName_, targetTableName_);
    if(!writer.open())
    {
        qWarning() << "Cannot open database " + targetFileName_ + " to write";
        return;
    }
    writer.write(sequencePoint);
}

ParsedPoint CSVPointListImporter::parseLine(const QString &line)
{
    const QStringList values = line.split(';');

    if(values.count() > 2)
    {
        return ParsedPoint();
    }

    return ParsedPoint(values.at(0),
                       values.at(1).toDouble());
}
