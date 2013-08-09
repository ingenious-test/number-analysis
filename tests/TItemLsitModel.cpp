#include "TItemLsitModel.h"

TItemLsitModel::TItemLsitModel(QObject *parent) :
    QObject(parent)
{
}

void TItemLsitModel::TestAddRemove_data()
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

void TItemLsitModel::TestAddRemove()
{
    QFETCH(SequencePointList, list);

    ItemModelList model;

    for(int i = 0; i < list.size(); i++)
    {
        model.addPointList(list[i]);
    }

    SequencePointList modelData;
    for(int i = 0; i < model.rowCount(); i++)
    {
        PointList modelRow;
        for(int j = 1; j < model.columnCount(); j++)
        {
             modelRow.append(model.data(model.index(i, j)).toDouble());
        }

        if(!modelRow.isEmpty())
        {
            modelRow.setID(model.data(model.index(i, 0)).toString());
            modelData.append(modelRow);
        }
    }

    const SequencePointList actualResult = modelData;
    const SequencePointList expectedResult = list;

    QCOMPARE(actualResult, expectedResult);
}
