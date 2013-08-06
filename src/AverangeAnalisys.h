#ifndef AVERANGEANALISYS_H

#define AVERANGEANALISYS_H

#include <QtCore>

Q_DECLARE_METATYPE(QList<double>)

class AverangeAnalisys
{
public:
    AverangeAnalisys();

    double analyze(const QList<double> &values);
};

#endif // AVERANGEANALISYS_H
