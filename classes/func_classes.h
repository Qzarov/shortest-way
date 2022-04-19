#ifndef CLASSES_H
#define CLASSES_H

#include <QVector>
#include <QDebug>
#include <QPoint>
#include <QQueue>

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
    int getNumOfPoints();
    double getRadius();

    // Debug
    void writeInDebug();

private:
    // Debug
    void writeInDebugCircle();
    void writeInDebugPolygon();

    AreaType type;
    QVector<QPoint> points;
    double radius;
};


// Graph


class Graph
{
public:
    Graph();
    Graph(int n_x, int n_y, QPoint s, QPoint f) :
        nodes_x(n_x), nodes_y(n_y),
        startP(s), finishP(f) {}
    void setWayPoints(QPoint s, QPoint f);
    void setDimension(int x_dim, int y_dim);

    // Restricted Areas
    void addArea(RestrictedArea new_area);
    void addPoint(QPoint p);
    size_t getAreasSize();
    QVector<RestrictedArea> getAreas();

    QVector<int> getRestrictedPoints();
    QVector<QPoint> getWay();
    void buildMatrix(QVector<int> restrP);
    void breadthFirstSearch();

private:
    bool isPointInCircle(QPoint p, int i);
    bool isPointInPolygon(QPoint p, int i);
    bool isPointRestricted(QPoint p);
    int getPointNum(QPoint p);
    QPoint getQPointFromNum(int p);
    void buildWay(int point_num);
    void writeAdjacInDebug();

    int nodes_x, nodes_y;
    QPoint startP;
    QPoint finishP;

    QVector<RestrictedArea> areas;
    QMap <int, QVector<int>> adjac;
    QMap<int, int> ancestor;
    int scale = 50;
    QVector<int> way;
};

#endif // CLASSES_H
