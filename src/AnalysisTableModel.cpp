#include "AnalysisTableModel.h"

AnalysisTableModel::AnalysisTableModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

AnalysisTableModel::AnalysisTableModel(const AnalysisCollection &colletions, const QList<PointList> &seq, QObject *parent):
    QAbstractItemModel(parent)
{
}


AnalysisTableModel::AnalysisTableModel(const AnalysisTableModel &analysisTableModel)
{

}

QModelIndex AnalysisTableModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex AnalysisTableModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int AnalysisTableModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int AnalysisTableModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant AnalysisTableModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

const IDList AnalysisTableModel::getHeaders()
{
    return IDList();
}

QList<AnalysisResult> AnalysisTableModel::analyze()
{
    return QList<AnalysisResult>();
}
