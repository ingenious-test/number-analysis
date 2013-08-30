#ifndef BANALYZING_H

#define BANALYZING_H

#include "../src/SqlPointListReader.h"
#include "../src/SqlPointListWriter.h"
#include "../src/AnalysisTableModel.h"

#include "../src/StupidAnalysis.h"
#include "../src/AverageAnalysis.h"
#include "../src/AverageIgnoreNullAnalysis.h"
#include "../src/StandardDeviationAnalysis.h"
#include "../src/MedianAnalysis.h"
#include "../src/FirstQuartileAnalysis.h"
#include "../src/ThirdQuartileAnalysis.h"

class BAnalyzing
{
public:
    BAnalyzing(const int pointsCount);

    void run();

private:
    int pointsCount_;
};

#endif // BANALYZING_H
