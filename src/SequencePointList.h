#ifndef SEQUENCEPOINTLIST_H
#define SEQUENCEPOINTLIST_H

#include "PointList.h"

class SequencePointList
{
  public:
    SequencePointList();
    inline const QList<PointList>& sequencesPoints() const { return sequencsePoints_;}
    inline const PointList& at(int i) const { return sequencsePoints_.at(i);}
    inline int count() const{ return sequencsePoints_.count();}

    inline void append(const PointList& pointList) {sequencsePoints_.append(pointList);}

    inline bool isEmpty() const { return sequencsePoints_.isEmpty();}
    bool isValid() const;

    QString toString() const;
    static bool fuzzyCompare(const SequencePointList& actual, const SequencePointList& expected);


    bool contains(const ID& id);


    inline SequencePointList &operator<< (const PointList &pointList)
    { append(pointList); return *this; }
    inline const PointList &operator[](int i) const { return sequencsePoints_[i];}
    inline PointList &operator[](int i) { return sequencsePoints_[i];}

    IDList getPointListIDs();
private:
    QList<PointList> sequencsePoints_;
};

#endif // SEQUENCEPOINTLIST_H
