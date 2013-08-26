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

    inline int count() const{ return list_.count();}

    inline bool isEmpty() const { return list_.isEmpty();}
    inline bool isValid() const { return !id_.isNull();}

    inline const QList<Point> &points() const { return list_;}
    inline QList<Point> clonePoints() const { return QList<Point>(list_);}
    inline const Point& at(int i) const { return list_.at(i);}

    inline void append(const Point& point) {list_.append(point);}
    inline void clear() {*this = PointList();}

    QString toString() const;

    static bool fuzzyCompare(const PointList& actual, const PointList& expected);

    static bool fuzzyComparePoints(const Point actual, const Point expected);


    inline const Point &operator[](int i) const { return list_[i];}
    inline Point &operator[](int i) { return list_[i];}

    inline PointList &operator<< (const Point &point)
    { append(point); return *this; }

private:
    ID id_;
    QList<Point> list_;
};

#endif // POINTLIST_H
