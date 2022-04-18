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
    radius = r*2;
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

int RestrictedArea::getNumOfPoints() { return points.size(); }


// Graph


Graph::Graph(){}

void Graph::buildMatrix(QVector<int> restrP)
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
    //writeAdjacInDebug();
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


void Graph::setWayPoints(QPoint s, QPoint f)
{
    startP = s;
    finishP = f;
}


void Graph::setDimension(int x_dim, int y_dim)
{
    nodes_x = x_dim;
    nodes_y = y_dim;
}


void Graph::addArea(RestrictedArea new_area)
{
    areas.push_back(new_area);
}


void Graph::addPoint(QPoint p)
{
    bool is_new_polyg = true;

    if (areas.size() == 0) {}
    else if (areas[areas.size() - 1].getType() == AreaType::Circle) {}
    else { is_new_polyg = false; }

    if (is_new_polyg) {
        RestrictedArea new_area(AreaType::Polygon);
        new_area.addPoint(p);
        areas.push_back(new_area);
        //new_area.writeInDebug();
    } else {
        areas[areas.size() - 1].addPoint(p);
        //areas[areas.size() - 1].writeInDebug();
    }
}


size_t Graph::getAreasSize() { return areas.size(); }
QVector<RestrictedArea> Graph::getAreas() { return areas; }


bool Graph::isPointInCircle(QPoint p, int i)
{
    double r = areas[i].getRadius();
    QPoint center = areas[i].getPoints()[0];
    double dx = p.rx()-center.rx();
    double dy = p.ry()-center.ry();
    double distance = sqrt(dx*dx + dy*dy);
    //qDebug() << "point: " << p.rx() << p.ry();
    //qDebug() << "center: " << center.rx() << center.ry();
    qDebug() << "distance: " << distance << ", r: " << r/2;
    if (distance >= r/2) { return false; }
    else { return true; }
}


bool Graph::isPointInPolygon(QPoint p, int i)
{
    QVector<QPoint> points = areas[i].getPoints();

    bool c = false;
    for (int i = 0, j = points.size() - 1; i < points.size(); j = i++)
    {
      QPoint ppi = points[i];//polygon point i
      QPoint ppj = points[j];//polygon point j
      if ((
        (ppi.ry() < ppj.ry()) && (ppi.ry() <= p.ry()) && (p.ry() <= ppj.ry()) &&
        ((ppj.ry() - ppi.ry()) * (p.rx() - ppi.rx()) > (ppj.rx() - ppi.rx()) * (p.ry() - ppi.ry()))
      ) || (
        (ppi.ry() > ppj.ry()) && (ppj.ry() <= p.ry()) && (p.ry() <= ppi.ry()) &&
        ((ppj.ry() - ppi.ry()) * (p.rx() - ppi.rx()) < (ppj.rx() - ppi.rx()) * (p.ry() - ppi.ry()))
      )) {
        c = !c;
      }
    }
    return c;
}


bool Graph::isPointRestricted(QPoint p)
{
    bool flag = false;
    //qDebug() << "areas.size(): " << areas.size();
    for (int i = 0; i < areas.size(); ++i) {
        //qDebug() << "type: " << (int)areas[i].getType();
        if (areas[i].getType() == AreaType::Circle) {
            flag = isPointInCircle(p, i);
        } else if (areas[i].getType() == AreaType::Polygon) {
            flag = isPointInPolygon(p, i);
        }
        qDebug() << "point: " << p.rx() << p.ry() << ", flag: " << flag;
        if (flag == true) { break; }
    }
    //qDebug() << "point: " << p.rx() << p.ry();

    return flag;
}


QVector<int> Graph::getRestrictedPoints()
{
    qDebug() << "getRestrictedPoints()!";
    QVector<int> restricted_points;
    int scale = 50;

    bool flag = false;
    for (int i = 0; i < nodes_y; ++i) {
        for (int j = 0; j < nodes_x; ++j) {
            flag = isPointRestricted(QPoint(i * scale, j * scale));
            //qDebug() << "point: " << i * scale << j * scale << ", flag: " << flag;
            if (flag) {
                restricted_points.push_back(i * nodes_x + j);
            }
        }
    }



    return restricted_points;
}
