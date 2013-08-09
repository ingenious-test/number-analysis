#ifndef POINTLIST_H

#define POINTLIST_H

#include <QtCore>

typedef QString ID;
typedef QHash<ID, int> IDHash;
typedef QList<ID> IDList;
typedef double Point;

class PointList : public QList<Point>
{
public:
    PointList(ID id = QString());
    PointList(ID id, const PointList& pointList);
    PointList& appendInc(const Point &t);

    void setID(const ID& id);
    const ID& id() const;
    bool isSetID() const;

    QString join(const QString c = QString(" : ")) const;

private:
    ID id_;
};
Q_DECLARE_METATYPE(PointList)

#endif // POINTLIST_H
