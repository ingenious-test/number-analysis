#ifndef POINTLIST_H
#define POINTLIST_H

#include <QtCore>

typedef QString ID;
typedef QList<ID> IDList;
typedef double Point;

class PointList
{
public:
    PointList();

    PointList(const ID& id);

    inline const ID& id() const { return id_;}
    inline void setID(const ID& id) { id_ = id;}

    inline int count() const{ return points_.count();}

    inline bool isEmpty() const { return points_.isEmpty();}
    inline bool isValid() const { return !id_.isNull();}

    QList<Point> points() const;
    const Point& at(int i) const;

    void append(const Point& point);
    void insert(const int ind, const Point& point);
    inline void clear() {*this = PointList();}

    QString toString() const;

    static bool fuzzyCompare(const PointList& actual, const PointList& expected);

    static bool fuzzyComparePoints(const Point actual, const Point expected);


    inline const Point &operator[](int i) const { return points_[i];}
    inline Point &operator[](int i) { return points_[i];}

    inline PointList &operator<< (const Point &point)
    { append(point); return *this; }

private:
    ID id_;
    QHash<int, Point> points_;
};

#endif // POINTLIST_H
