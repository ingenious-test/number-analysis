#ifndef POINTLISTSTORAGESTATISTICS_H

#define POINTLISTSTORAGESTATISTICS_H

#include <QtCore>

typedef QString IDStatistics;
typedef QList<IDStatistics> IDStatisticsList;


class PointListStatistics
{
public:
    PointListStatistics() : id_(IDStatistics()), value_(QVariant()) {}
    PointListStatistics(const IDStatistics& id, const QVariant& value) :
        id_(id), value_(value)
    {}

    inline const IDStatistics &id() const { return id_;}
    inline const QVariant &value() const { return value_;}

private:
    IDStatistics id_;
    QVariant value_;
};

class PointListStorageStatistics
{
public:
    PointListStorageStatistics();

    void appendStatistics(const PointListStatistics &statistics);
    void removeStatistics(const IDStatistics &id);

    const QVariant value(const IDStatistics &id);

    const QStringList toString();

    int size() const;
    bool contains(const IDStatistics &id) const;

    inline PointListStorageStatistics &operator<< (const PointListStatistics &statistics)
    { appendStatistics(statistics); return *this; }


private:
    QHash<IDStatistics, QVariant> statistics_;

};

#endif // POINTLISTSTORAGESTATISTICS_H
