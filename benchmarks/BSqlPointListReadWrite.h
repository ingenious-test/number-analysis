#ifndef BSQLPOINTLISTREADWRITE_H

#define BSQLPOINTLISTREADWRITE_H

#include "../src/SqlPointListReader.h"
#include "../src/SqlPointListWriter.h"

class BSqlPointListReadWrite
{
public:
    BSqlPointListReadWrite(const int pointsCount);

    void runRead();
    void runWrite();

private:
    int pointsCount_;
};

#endif // BSQLPOINTLISTREADWRITE_H
