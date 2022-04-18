#include "func_classes.h"

// RestrictedArea

void RestrictedArea::addPoint(QPoint p)
{
    points.push_back(p);
}


QVector<QPoint> RestrictedArea::getPoints()
{
    return points;
}


RestrictedArea::RestrictedArea(QPoint p, float r)
{
    type = AreaType::Circle;
    points.push_back(p);
    radius = r;
}


void RestrictedArea::delPoint(int n){ ; } //coming soon

bool RestrictedArea::isIntersected(){ return true; } //coming soon
void RestrictedArea::print(){ ; } //coming soon

AreaType RestrictedArea::getType() { return type; }
void RestrictedArea::setType(AreaType t) { type = t;}


double RestrictedArea::getRadius()
{
    return radius;
}


void RestrictedArea::writeInDebugCircle()
{
    qDebug() << "center: x:" << points[0].rx() << ", y: " << points[0].ry()
             << ", r: " << radius;
}

void RestrictedArea::writeInDebugPolygon()
{
    for (int i=0; i < points.size(); ++i){
        qDebug() << i << "point, x: " << points[i].rx() << ", y: " << points[i].ry();
    }
}


void RestrictedArea::writeInDebug()
{
    qDebug() << "AREA: ";
    if (type == AreaType::Circle) {
        qDebug() << " circle";
        writeInDebugCircle();
    } else if (type == AreaType::Polygon) {
        qDebug() << " polygon";
        writeInDebugPolygon();
    }
}

// Graph

Graph::Graph(){}

void Graph::buildMatrix()
{
    int nodes = nodes_x*nodes_y;
    for (int i = 0; i < nodes; ++i){
        for (int j = 0; j < nodes; ++j) {
            if (abs(i - j) == 1 ||
                abs(i - j) == nodes_x) {
                adjac[i].push_back(j);
            }
        }
    }
    writeAdjacInDebug();
}


void Graph::writeAdjacInDebug()
{
    qDebug() << "nodes_x: " << nodes_x << ", nodes_y: " << nodes_y;
    QMapIterator it(adjac);
    while (it.hasNext()){
        it.next();
        qDebug() << it.key() << " : ";
        for (int i = 0; i < it.value().size(); ++i) {
            qDebug() << it.value()[i] << " ";
        }
        qDebug() << "NEXT";
    }
}
