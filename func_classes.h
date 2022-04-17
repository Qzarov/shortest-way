#ifndef CLASSES_H
#define CLASSES_H

#include <QVector>
#include <QDebug>
#include <QPoint>

/*
//template<typename T>
class Point
{
public:
    Point() : x(0), y(0) {}
    //Point(T x_new, T y_new) : x(x_new), y(y_new) {}
    Point(int x_new, int y_new) : x(x_new), y(y_new) {}

    //T x, y;
    int x, y;
};*/


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

    QVector<QPoint> getPoints();
    void addPoint(QPoint p);
    void delPoint(int n); //coming soon

    bool isIntersected(); //coming soon
    void print(); //coming soon

    AreaType getType();
    void setType(AreaType t);

    void writeInDebug();

private:
    void writeInDebugCircle();
    void writeInDebugPolygon();

    AreaType type;
    QVector<QPoint> points;
    float radius;
};

class Grapf
{

};

#endif // CLASSES_H
