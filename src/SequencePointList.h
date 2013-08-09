#ifndef SEQUENCEPOINTLIST_H

#define SEQUENCEPOINTLIST_H

#include "PointList.h"

class SequencePointList : public QList<PointList>
{
public:
    SequencePointList();
    SequencePointList& appendInc( ID id, PointList& pointList);
    void append( ID id, const PointList &pointList);
    void append(const PointList &pointList);

    int containsID(const ID& id);

    QStringList join(const QString c = QString(" : ")) const;

    IDList getIDs() const;

};
Q_DECLARE_METATYPE(SequencePointList)

#endif // SEQUENCEPOINTLIST_H
