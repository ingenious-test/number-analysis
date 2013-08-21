#include "TItemListModel.h"

TItemListModel::TItemListModel(QObject *parent) :
    QObject(parent)
{
}

void TItemListModel::TestAddRemoveMoc_data()
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
                               << (IDList() << "Айди-Два" << "Айди-Один");

    QTest::newRow("five-none-sort") << (IDList() << "id5" << "id3" << "id4" << "id1" << "id2")
                                    << (IDList() << "id1" << "id2" << "id3" << "id4" << "id5");

    QTest::newRow("six-none-sort") << (IDList() << "id3" << "id1" << "id4" << "id2" << "id6" << "id5")
                                   << (IDList() << "id1" << "id2" << "id3" << "id4" << "id5" << "id6");

    QTest::newRow("seven-none-sort") << (IDList() << "id6" << "id4" << "id2" << "id1" << "id3" << "id7" << "id5")
                                     << (IDList() << "id1" << "id2" << "id3" << "id4" << "id5" << "id6" << "id7");
}

void TItemListModel::TestAddRemoveMoc()
{
    QFETCH(IDList, list);
    QFETCH(IDList, result);

    MocPointListReader reader(list);

    ItemListModel model(&reader);

    IDList items;
    for(int i = 0; i < model.rowCount(); i++)
    {
        items.append(model.index(i, 0).data().toString());
    }

    const IDList actualData = items;
    const IDList expectedData = result;

    QCOMPARE(actualData, expectedData);
}

void TItemListModel::TestAddRemoveSql_data()
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

    QTest::newRow("utf-8-id") << (IDList() << ID("Айди-Один"))
                              << (IDList() << ID("Айди-Один"));

    QTest::newRow("utf-8-ids") << (IDList() << ID("Айди-Один") << ID("Айди-Два"))
                               << (IDList() << ID("Айди-Два") << ID("Айди-Один"));
}

void TItemListModel::TestAddRemoveSql()
{
    QFETCH(IDList, list);
    QFETCH(IDList, result);

    const QString dataBaseName = QString(QTest::currentDataTag()) + "TestAddRemoveSql.db";
    const QString tableName = "Points";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    SqlPointListWriter writer(dataBaseName, tableName);
    writer.open();
    {
        foreach(const ID& item, list)
        {
            writer.write(item, PointList() << Point(1.0));
        }
    }

    SqlPointListReader reader(dataBaseName, tableName);
    reader.open();

    ItemListModel model(&reader);

    IDList items;
    for(int i = 0; i < model.rowCount(); i++)
    {
        items.append(model.index(i, 0).data().toString());
    }

    const IDList actualData = items;
    const IDList expectedData = result;

    QCOMPARE(actualData, expectedData);
}
