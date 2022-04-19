#include "func_classes.h"

Graph::Graph(){}

void Graph::buildMatrix(QVector<int> restrP)
{
    adjac.clear();
    int nodes = nodes_x*nodes_y;
    for (int i = 0; i < nodes; ++i){
        if (restrP.contains(i)) { continue; }
        for (int j = 0; j < nodes; ++j) {
            if (restrP.contains(j) ||
               (((i+1) % nodes_y == 0) && (j % nodes_y == 0)) ||
               (((j+1) % nodes_y == 0) && (i % nodes_y == 0))
                    ) {
                continue;
            }

            if ((abs(i - j) == 1) ||
                abs(i - j) == nodes_x) {
                adjac[i].push_back(j);
            }
        }
    }
    //writeAdjacInDebug();
}


QVector<int> Graph::getRestrictedPoints()
{
    QVector<int> restricted_points;

    bool flag = false;
    for (int i = 0; i < nodes_y; ++i) {
        for (int j = 0; j < nodes_x; ++j) {
            flag = isPointRestricted(QPoint(i * scale, j * scale));
            if (flag) {
                restricted_points.push_back(j * nodes_x + i);
            }
        }
    }
    /*
    qDebug() << "Restricted points:";
    for (int i = 0; i < restricted_points.size(); ++i)
    {
        qDebug() << restricted_points[i] <<
                    restricted_points[i] / nodes_x * scale <<
                    restricted_points[i] % nodes_x * scale;
    }
    */
    return restricted_points;
}


void Graph::writeAdjacInDebug()
{
    qDebug() << "nodes_x: " << nodes_x << ", nodes_y: " << nodes_y;
    QMapIterator it(adjac);
    while (it.hasNext()){
        it.next();
        qDebug() << it.key() << " : " << it.value();
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

    if (distance > r/2) { return false; }
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
    for (int i = 0; i < areas.size(); ++i) {
        if (areas[i].getType() == AreaType::Circle) {
            flag = isPointInCircle(p, i);
        } else if (areas[i].getType() == AreaType::Polygon) {
            flag = isPointInPolygon(p, i);
        }
        if (flag == true) { break; }
    }

    return flag;
}


int Graph::getPointNum(QPoint p)
{
    return (p.rx() / scale) + (p.ry() / scale) * nodes_x;
}


void Graph::breadthFirstSearch()
{
    int nodes = nodes_x*nodes_y;

    ancestor.clear();
    QVector<bool> passed(nodes, false);;
    QVector<int> distance(nodes, 10000);

    int start = getPointNum(startP);
    passed[start] = true;
    ancestor[start] = start;
    distance[start] = 0;
    QQueue<int> queue;
    queue.enqueue(start);

    while(!queue.isEmpty()) {
        int u = queue.head();
        queue.dequeue();
        for (int i = 0; i < adjac[u].size(); ++i) {
            int v = adjac[u][i];
            if (!passed[v]) {
                passed[v] = true;
                ancestor[v] = u;
                distance[v] = distance[u] + 1;
                queue.enqueue(v);
            }
        }
    }

    int finish = getPointNum(finishP);
    qDebug() << "DA WEI to " << finish;
    way.clear();
    buildWay(finish);
    qDebug() << way;
}


void Graph::buildWay(int point_num)
{
    if (ancestor[point_num] != point_num) {
        buildWay(ancestor[point_num]);
    }
    way.push_back(point_num);
}

QPoint Graph::getQPointFromNum(int p)
{
    return QPoint(p % nodes_x * scale, p / nodes_x * scale);
}


QVector<QPoint> Graph::getWay()
{
    QVector<QPoint> res;

    for (int i = 0; i < way.size(); ++i) {
        res.push_back(getQPointFromNum(way[i]));
    }
    return res;
}
