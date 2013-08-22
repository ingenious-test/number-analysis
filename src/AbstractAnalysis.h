#ifndef ABSTRACTANALYSIS_H

#define ABSTRACTANALYSIS_H

#include <QtCore>

typedef QString IDAnalysis;
typedef QList<IDAnalysis> IDAnalysisList;

typedef QString ID;
typedef QList<ID> IDList;


typedef double Point;
class PointList
{
public:
    PointList() :
        id_(QString()) {}

    PointList(const ID& id) :
        id_(id) {}

    inline const ID& id() const { return id_;}
    inline void setID(const ID& id) { id_ = id;}

    inline int count() const{ return list_.count();}

    inline bool isEmpty() const { return list_.isEmpty();}
    inline bool isValid() const { return !id_.isNull();}

    inline const QList<Point> &points() const { return list_;}
    inline const Point& at(int i) const { return list_.at(i);}

    inline void append(const Point& point) {list_.append(point);}

    inline const Point &operator[](int i) const { return list_[i];}
    inline Point &operator[](int i) { return list_[i];}

    inline PointList &operator<< (const Point &point)
    { append(point); return *this; }

private:
    ID id_;
    QList<Point> list_;
};

class SequencePointList
{
  public:

    inline const QList<PointList>& sequencesPoints() const { return sequencsePoints_;}
    inline const PointList& at(int i) const { return sequencsePoints_.at(i);}
    inline int count() const{ return sequencsePoints_.count();}

    inline void append(const PointList& pointList) {sequencsePoints_.append(pointList);}

    inline bool isEmpty() const { return sequencsePoints_.isEmpty();}
    inline bool isValid() const
    {
        foreach(const PointList pointList, sequencesPoints())
        {
            const bool isValidList = pointList.isValid();
            if(!isValidList)
            {
                return false;
            }
        }

        return true;
    }

    inline SequencePointList &operator<< (const PointList &pointList)
    { append(pointList); return *this; }
    inline const PointList &operator[](int i) const { return sequencsePoints_[i];}
    inline PointList &operator[](int i) { return sequencsePoints_[i];}

    IDList getPointListIDs()
    {
        IDList idList;
        foreach(const PointList& pointList, sequencesPoints())
        {
            idList << pointList.id();
        }
        return idList;
    }

private:
    QList<PointList> sequencsePoints_;
};


class AbstractAnalysis
{
    friend class AverageAnalysis;
    friend class AverageIgnoreNullAnalysis;
    friend class StupidAnalysis;

public:
    static double listSum(const PointList &list);

    virtual double analyze(const PointList &list) const = 0;
    virtual AbstractAnalysis* clone() = 0;

    virtual bool isValid() const;

    IDAnalysis id() const;

protected:
    AbstractAnalysis(const IDAnalysis &id);

private:
    IDAnalysis id_;
};

Q_DECLARE_METATYPE(AbstractAnalysis*)

#endif // ABSTRACTANALYSIS_H
