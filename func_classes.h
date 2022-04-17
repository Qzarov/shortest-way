#ifndef CLASSES_H
#define CLASSES_H

#include <QVector>
#include <QDebug>
#include <QPoint>

enum class AreaType {
    Circle,
    Polygon,
    Permitted
};


class RestrictedArea
{
public:
    RestrictedArea() = delete;
    RestrictedArea(AreaType t) : type(t) {}
    RestrictedArea(QPoint p, float r);

    void addPoint(QPoint p);
    void setType(AreaType t);
    void delPoint(int n); //coming soon

    bool isIntersected(); //coming soon
    void print(); //coming soon

    AreaType getType();
    QVector<QPoint> getPoints();
    double getRadius();

    void writeInDebug();

private:
    void writeInDebugCircle();
    void writeInDebugPolygon();

    AreaType type;
    QVector<QPoint> points;
    double radius;
};

class Grapf
{

};

#endif // CLASSES_H
