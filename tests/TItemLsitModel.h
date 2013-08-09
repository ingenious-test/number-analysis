#ifndef TITEMLSITMODEL_H

#define TITEMLSITMODEL_H

#include <QTest>

#include "../src/ItemModelList.h"

class TItemLsitModel : public QObject
{
    Q_OBJECT

public:
    TItemLsitModel(QObject *parent = 0);

private slots:
    void TestAddRemove_data();
    void TestAddRemove();
    
};

#endif // TITEMLSITMODEL_H
