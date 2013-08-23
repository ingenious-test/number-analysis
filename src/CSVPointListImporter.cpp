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
    if(!CSVPointListValidator::validation(sourceFileName_))
    {
        qWarning() << sourceFileName_ << "is not valid";
        return;
    }

    QFile file(sourceFileName_);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << sourceFileName_ << " not open";
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

        if((lastID !=  parsedLine.id))
        {
            if(!sequencePoint.contains(lastID))
            {
                tempPointList.setID(lastID);
                sequencePoint.append(tempPointList);
                tempPointList.clear();
            }
        }

        tempPointList.append(parsedLine.value);

        if(file.atEnd())
        {
            if((lastID !=  parsedLine.id))
            {
                lastID = parsedLine.id;
            }

            if(!sequencePoint.contains(lastID))
            {
                tempPointList.setID(lastID);
                sequencePoint.append(tempPointList);
                tempPointList.clear();
            }
        }

        lastID = parsedLine.id;
    }

    file.flush();
    file.close();

    if(!sequencePoint.isEmpty())
    {

        SqlPointListWriter writer(targetFileName_, targetTableName_);
        if(!writer.open())
        {
            qWarning() << "Cannot open database " + targetFileName_ + " to write";
            return;
        }
        writer.write(sequencePoint);
    }
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
