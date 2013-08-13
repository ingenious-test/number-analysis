#ifndef TITEMLISTMODEL_H

#define TITEMLISTMODEL_H

#include <QTest>

#include "../src/ItemListModel.h"
#include "../src/SqlPointListReader.h"
#include "../src/SqlPointListWriter.h"

class TItemListModel : public QObject
{
    Q_OBJECT

public:
    TItemListModel(QObject *parent = 0);

private slots:
    void TestAddRemoveMoc_data();
    void TestAddRemoveMoc();

    void TestAddRemoveSql_data();
    void TestAddRemoveSql();
};

#endif // TITEMLISTMODEL_H
