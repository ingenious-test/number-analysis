#ifndef METATYPES_H

#define METATYPES_H

#include <QtCore>

#include "AnalysisTableModel.h"
#include "PointListStorageStatistics.h"
#include "StatisticsCollection.h"
#include "CSVPointListImporter.h"

Q_DECLARE_METATYPE(IDList)
Q_DECLARE_METATYPE(PointList)
Q_DECLARE_METATYPE(SequencePointList)
Q_DECLARE_METATYPE(AnalysisResult)
Q_DECLARE_METATYPE(AnalysisResults)
Q_DECLARE_METATYPE(AnalysisList)
Q_DECLARE_METATYPE(PointListStorageStatistics)
Q_DECLARE_METATYPE(PointListStatistics)
Q_DECLARE_METATYPE(Qt::SortOrder)
Q_DECLARE_METATYPE(AbstractStatictics*)
Q_DECLARE_METATYPE(AbstractAnalysis*)
Q_DECLARE_METATYPE(ParsedPoint)
Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(QList<Point>)

#endif // METATYPES_H
