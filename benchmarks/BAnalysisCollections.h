#ifndef BANALYSISCOLLECTIONS_H

#define BANALYSISCOLLECTIONS_H

#include "../src/AnalysisCollection.h"
#include "../src/StupidAnalysis.h"

class BAnalysisCollections
{
public:
    BAnalysisCollections(const int nRuns);

    void run();

private:
    int nRuns_;
};

#endif // BANALYSISCOLLECTIONS_H
