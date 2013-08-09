#include "TItemListModel.h"

TItemListModel::TItemListModel(QObject *parent) :
    QObject(parent)
{
}

void TItemListModel::TestAddRemove_data()
{
    QTest::addColumn<SequencePointList>("list");


    QTest::newRow("empty") << SequencePointList();

    QTest::newRow("one-pointlist") << SequencePointList()
                                      .appendInc("Первый",
                                                 PointList()
                                                 .appendInc(1.0)
                                                 .appendInc(2.4)
                                                 .appendInc(5.6));

    QTest::newRow("two-pointlist") << SequencePointList()
                                      .appendInc("Первый",
                                                 PointList()
                                                 .appendInc(2.0)
                                                 .appendInc(5.1)
                                                 .appendInc(3.2))
                                      .appendInc("Второй",
                                                 PointList()
                                                 .appendInc(3.4)
                                                 .appendInc(1.2)
                                                 .appendInc(9.6)
                                                 .appendInc(2.2));

    QTest::newRow("two-pointlist") << SequencePointList()
                                      .appendInc("Первый",
                                                 PointList()
                                                 .appendInc(4.5)
                                                 .appendInc(12.4)
                                                 .appendInc(0.6))
                                      .appendInc("Второй",
                                                 PointList()
                                                 .appendInc(2.4)
                                                 .appendInc(3.2)
                                                 .appendInc(7.6)
                                                 .appendInc(2.2))
                                      .appendInc("Третий",
                                                 PointList()
                                                 .appendInc(1.4)
                                                 .appendInc(3.4)
                                                 .appendInc(7.7));
}

void TItemListModel::TestAddRemove()
{
    QFETCH(SequencePointList, list);

    ItemListModel model(list);

    SequencePointList dataFromModel;
    for(int i = 0; i < model.rowCount(); i++)
    {
        dataFromModel.append(qvariant_cast<PointList>(model.data(model.index(i, 0))));
    }

    const SequencePointList actualData = dataFromModel;
    const SequencePointList expectedData = list;

    QCOMPARE(actualData, expectedData);
}
