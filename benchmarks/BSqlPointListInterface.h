#ifndef BSQLPOINTLISTINTERFACE_H

#define BSQLPOINTLISTINTERFACE_H

#include "../src/SqlPointListReader.h"
#include "../src/SqlPointListWriter.h"

#include "../src/ItemListModel.h"
#include "../src/AnalysisTableModel.h"

class BSqlPointListInterface
{
public:
    BSqlPointListInterface(const int nRuns);

    void run();

private:
    int nRuns_;

};

#endif // BSQLPOINTLISTINTERFACE_H
