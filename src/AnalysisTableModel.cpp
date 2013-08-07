#include "AnalysisTableModel.h"
#include "QStandardItemModel"


AnalysisTableModel::AnalysisTableModel(QObject *parent) :
    QAbstractItemModel(parent), collection_(NULL)
{

}

AnalysisTableModel::AnalysisTableModel(AnalysisCollection *colletions, const SequencePointList &seq, QObject *parent):
    QAbstractItemModel(parent)
{
    collection_ = colletions;
    seqPointList_ = seq;
}


AnalysisTableModel::AnalysisTableModel(const AnalysisTableModel &analysisTableModel):
    collection_(NULL)
{
    if(analysisTableModel.collection_ != NULL)
    {
        collection_ = analysisTableModel.collection_->clone();
    }
    seqPointList_ = analysisTableModel.seqPointList_;
}

AnalysisTableModel::~AnalysisTableModel()
{
    if(collection_ != NULL)
    {
        delete collection_;
    }
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
    return results_.length();
}

int AnalysisTableModel::columnCount(const QModelIndex &parent) const
{
    if(collection_ != NULL)
    {
        return collection_->length();
    }
    return 0;
}

QVariant AnalysisTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if(collection_ == NULL)
    {
        return QVariant();
    }

    QStringList list = collection_->getNameList();

    bool isValidColumn = (index.column() > -1) && (index.column() < list.length());

    if(!isValidColumn)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return results_.at(index.row()).value(list.at(index.column()),0);
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

    if(collection_ == NULL)
    {
        return QVariant();
    }

    QStringList list = collection_->getNameList();

    bool isValidSection = (section > -1) && (section < list.length());

    if(!isValidSection)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        return list.at(section);
    }

    if (orientation == Qt::Vertical)
    {
        return QString::number(section+1);
    }

    return QVariant();
}

IDList AnalysisTableModel::getHeaders()
{
    if(collection_ != NULL)
    {
        return collection_->getNameList();
    }
    return IDList();
}

void AnalysisTableModel::analyze()
{
    if(collection_ != NULL)
    {
        if(!seqPointList_.isEmpty())
        {
            results_.clear();
            foreach(PointList item, seqPointList_)
            {
                results_.append(collection_->analyze(item));
            }
        }
    }
}

const AnalysisResults &AnalysisTableModel::Results()
{
    return results_;
}

AnalysisCollection *AnalysisTableModel::analysisCollection()
{
    return collection_;
}

void AnalysisTableModel::setAnalysisCollection(AnalysisCollection *collection)
{
    if(collection != NULL)
    {
        collection_ = collection;
    }
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
