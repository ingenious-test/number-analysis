#include "Widget.h"
#include "src/ItemListDelegate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;

    AnalysisList list;
    list
            .insertInc(new StupidAnalysis(1.0))
            .insertInc(new AverageIgnoreNullAnalysis())
            .insertInc(new AverageAnalysis)
            ;

    analyzesModel_ = new AnalysisTableModel(list);

    analyzesView_ = new QTableView();

    analyzesView_->setModel(analyzesModel_);

    seqPointListModel_ = new ItemListModel(
                SequencePointList()
                .appendInc("Первая",
                           PointList()
                           .appendInc(3.0)
                           .appendInc(4.0)
                           .appendInc(5.0)
                           )
                .appendInc("Вторая",
                           PointList()
                           .appendInc(8.0)
                           .appendInc(4.0)
                           .appendInc(19.0)
                           .appendInc(13.0)
                           )
                );

    seqPointListView_ = new QListView();
    seqPointListView_->setItemDelegate(new ItemListDelegate());
    seqPointListView_->setFixedWidth(300);
    seqPointListView_->setModel(seqPointListModel_);

    mainLayout->addWidget(seqPointListView_);
    mainLayout->addWidget(analyzesView_);


    setLayout(mainLayout);

    QObject::connect(seqPointListView_, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(pointsListDoubleCLicked(QModelIndex)));
}

Widget::~Widget()
{

}

void Widget::pointsListDoubleCLicked(QModelIndex index)
{
    if(seqPointListView_->currentIndex().isValid())
    {
        PointList pointList = qvariant_cast<PointList>(seqPointListModel_->data(index));

        bool isContains = analyzesModel_->containsPointList(pointList) > -1;

        if(!isContains)
        {
            analyzesModel_->addPointList(pointList);
        }
        else
        {
            qWarning() << "Point list " + pointList.id() + " has already been added to the analysis";
        }
    }
}
