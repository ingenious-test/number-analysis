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

    QTest::newRow("one-pointlist") << (IDList() << "id1")
                                   << (IDList() << "id1");

    QTest::newRow("two-pointlist1") << (IDList() << "id1" << "id2")
                                    << (IDList() << "id1" << "id2");

    QTest::newRow("three-pointlist") << (IDList() << "id1" << "id2" << "id3")
                                     << (IDList() << "id1" << "id2" << "id3");

    QTest::newRow("four-pointlist-with-empty") << (IDList() << "id1" << "id2" << "" << "id3")
                                               << (IDList() << "" << "id1" << "id2" << "id3");

    QTest::newRow("four-pointlist-with-repeat") << (IDList() << "id1" << "id2" << "id3" << "id1")
                                                << (IDList() << "id1" << "id2" << "id3");

    QTest::newRow("utf-8-id") << (IDList() << "Айди-Один")
                              << (IDList() << "Айди-Один");

    QTest::newRow("utf-8-ids") << (IDList() << "Айди-Один" << "Айди-Два")
                               << (IDList() << "Айди-Один" << "Айди-Два");
}

void TItemListModel::TestAddRemove()
{
    QFETCH(IDList, list);
    QFETCH(IDList, result);

    MocPointListReader reader(list);

    ItemListModel model(&reader);

    IDList idList;
    for(int i = 0; i < model.rowCount(); i++)
    {
        idList.append(model.index(i,0).data().toString());
    }

    const IDList actualData = idList;
    const IDList expectedData = result;

    QCOMPARE(actualData, expectedData);
}
