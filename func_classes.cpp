#include "func_classes.h"

//RestrictedArea::RestrictedArea(){}

void RestrictedArea::addPoint(Point p)
{
    points.push_back(p);
}


QVector<Point> RestrictedArea::getPoints()
{
    return points;
}


RestrictedArea::RestrictedArea(Point p, float r)
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


void RestrictedArea::writeInDebugCircle()
{
    qDebug() << "center: x:" << points[0].x << ", y: " << points[0].y
             << ", r: " << radius;
}

void RestrictedArea::writeInDebugPolygon()
{
    for (int i=0; i < points.size(); ++i){
        qDebug() << i << "point, x: " << points[i].x << ", y: " << points[i].y;
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
