#ifndef BSQLPOINTLISTREADWRITE_H

#define BSQLPOINTLISTREADWRITE_H

#include "../src/SqlPointListReader.h"
#include "../src/SqlPointListWriter.h"

class BSqlPointListReadWrite
{
public:
    BSqlPointListReadWrite(const int nRuns_);

    void run();

private:
    int nRuns_;
};

#endif // BSQLPOINTLISTREADWRITE_H
