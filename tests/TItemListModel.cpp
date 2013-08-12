#include "TItemListModel.h"

TItemListModel::TItemListModel(QObject *parent) :
    QObject(parent)
{
}

void TItemListModel::TestAddRemove_data()
{
    QTest::addColumn<IDList>("list");
    QTest::addColumn<IDList>("result");

    QTest::newRow("empty") << IDList() << IDList();

    QTest::newRow("one-pointlist") << (IDList() << "Первый")
                                   << (IDList() << "Первый");

    QTest::newRow("two-pointlist") << (IDList() << "Первый" << "Второй")
                                   << (IDList() << "Первый" << "Второй");

    QTest::newRow("two-pointlist") << (IDList() << "Первый" << "Второй" << "Третий")
                                   << (IDList() << "Первый" << "Второй" << "Третий");

    QTest::newRow("four-pointlist-with-empty") << (IDList() << "Первый" << "Второй" << "" << "Третий")
                                               << (IDList() << "Первый" << "Второй" << "Третий");

    QTest::newRow("four-pointlist-with-repeat") << (IDList() << "Первый" << "Второй" << "Третий" << "Первый")
                                                   << (IDList() << "Первый" << "Второй" << "Третий");
}

void TItemListModel::TestAddRemove()
{
    QFETCH(IDList, list);
    QFETCH(IDList, result);

    ItemListModel model;
    model.appendPointList(list);

    IDList idList;
    for(int i = 0; i < model.rowCount(); i++)
    {
        idList.append(model.index(i,0).data().toString());
    }

    const IDList actualData = idList;
    const IDList expectedData = result;

    QCOMPARE(actualData, expectedData);
}
