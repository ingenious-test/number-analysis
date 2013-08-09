#ifndef TITEMLISTMODEL_H

#define TITEMLISTMODEL_H

#include <QTest>

#include "../src/ItemListModel.h"

class TItemListModel : public QObject
{
    Q_OBJECT

public:
    TItemListModel(QObject *parent = 0);

private slots:
    void TestAddRemove_data();
    void TestAddRemove();
    
};

#endif // TITEMLISTMODEL_H
