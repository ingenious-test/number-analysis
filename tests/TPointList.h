#ifndef TPOINTLIST_H

#define TPOINTLIST_H

#include <QTest>

#include "../src/PointList.h"
#include "../src/Metatypes.h"

class TPointList : public QObject
{
    Q_OBJECT
public:
    TPointList();
    
private:
    void TestToList_data();
    void TestToList();
    
};

#endif // TPOINTLIST_H
