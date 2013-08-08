#include "AnalysisTableModel.h"
#include "QStandardItemModel"


AnalysisTableModel::AnalysisTableModel(QObject *parent) :
    QAbstractItemModel(parent)
{

}

AnalysisTableModel::AnalysisTableModel(const AnalysisCollection& colletions, const SequencePointList &seq, QObject *parent):
    QAbstractItemModel(parent), collection_(colletions)
{

    seqPointList_ = seq;
}

AnalysisTableModel::~AnalysisTableModel()
{

}

QModelIndex AnalysisTableModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex AnalysisTableModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int AnalysisTableModel::rowCount(const QModelIndex &parent) const
{
    return idResults_.size();
}

int AnalysisTableModel::columnCount(const QModelIndex &parent) const
{
    return collection_.size() + 1;
}

QVariant AnalysisTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    IDAnalysisList listAnalysis = collection_.getNameList();

    if (role == Qt::DisplayRole)
    {
        if(results_.isEmpty())
        {
            return 0;
        }

        QList<ID> listResults = results_.keys();
        if(index.column() == 0)
        {
            return listResults.at(index.row());
        }
        else
        {
            return results_.value(listResults.at(index.row())).value(listAnalysis.at(index.column() - 1),0);
        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
}

QVariant AnalysisTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    QStringList list = collection_.getNameList();

    if (orientation == Qt::Horizontal)
    {
        if(section == 0)
        {
            return QString("Идентификатор результата");
        }
        else
        {
            return list.at(section-1);
        }
    }

    if (orientation == Qt::Vertical)
    {
        return QString::number(section+1);
    }

    return QVariant();
}

IDAnalysisList AnalysisTableModel::getHeaders()
{
    return collection_.getNameList();
}

void AnalysisTableModel::analyze()
{
    if(collection_.size() > 0)
    {
        results_.clear();
        if(idResults_.isEmpty())
        {
            qWarning() << "Set ID for Results";
            return ;
        }

        if(idResults_.size() != seqPointList_.size())
        {
            qWarning() << "ID must be set to all results (need "
                          + QString::number(seqPointList_.size()) + " ID results. ";
            qWarning() << "You have only " + QString::number(idResults_.size()) + " ID results. ";
            return;
        }
        QList<ID> idResultsList = idResults_.toList();

        for(int i = 0; i < seqPointList_.length(); i++)
        {
            results_.insert(idResultsList[i], collection_.analyze(seqPointList_[i]));
        }
    }
}

const AnalysisResults &AnalysisTableModel::Results()
{
    return results_;
}

const AnalysisCollection &AnalysisTableModel::analysisCollection()
{
    return collection_;
}

AnalysisCollection &AnalysisTableModel::addAnalysis(AbstractAnalysis *analysis)
{
    return collection_.addAnalysis(analysis);
}

void AnalysisTableModel::removeAnalysis(const QString &name)
{
    removeAnalysis(name);
}

void AnalysisTableModel::clearAnalyses()
{
    collection_.removeAll();
}

const SequencePointList &AnalysisTableModel::sequencePointList()
{
    return seqPointList_;
}

void AnalysisTableModel::addPointList(const PointList &pointList)
{
    seqPointList_.append(pointList);
}

void AnalysisTableModel::removePointList(const int index)
{
    bool isValidIndex = (index > -1) && (index < seqPointList_.length());

    if(isValidIndex)
    {
        seqPointList_.removeAt(index);
    }
}

const IDSet &AnalysisTableModel::getIDs()
{
    return this->idResults_;
}

bool AnalysisTableModel::insertID(const ID &id)
{
    if(!idResults_.contains(id))
    {
        idResults_.insert(id);
        return true;
    }
    else
    {
        qWarning() << "ID " + id + " exists";
        return false;
    }
}

void AnalysisTableModel::insertID(const IDSet &idSet)
{
    foreach(ID id, idSet)
    {
        insertID(id);
    }
}

bool AnalysisTableModel::removeID(const ID &id)
{
    if(idResults_.contains(id))
    {
        return idResults_.remove(id);
    }
    else
    {
        qWarning() << "ID " + id + " not exists";
        return false;
    }
    return false;
}
