#ifndef AVERANGEANALISYS_H

#define AVERANGEANALISYS_H

#include "AbstractAnalysis.h"

Q_DECLARE_METATYPE(QList<double>)

class AverangeAnalisys : public AbstractAnalysis
{
public:
    AverangeAnalisys();

    double analyze(const QList<double> &values) const;
};

#endif // AVERANGEANALISYS_H
