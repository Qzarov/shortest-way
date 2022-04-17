#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QGridLayout>

//#include "shortestway.h"
#include "func_classes.h"

namespace Ui {
class Graphics;
}

class Graphics : public QDialog
{
    Q_OBJECT

public:
    Graphics(QVector<RestrictedArea> ar, QWidget *parent = nullptr);
    //Graphics(QWidget *parent = nullptr);
    ~Graphics();

    void setBoundaries(int x_l, int x_r, int y_l, int y_u);
    void setDimension(int x_d, int y_d);
    void setWayPoints(QPoint s, QPoint f);

    void drawAll();

private:
    void configTools();
    void drawGrid();
    void drawWayPoints();
    void drawAreas();

    Ui::Graphics *ui;
    QVector<RestrictedArea> areas;
    QPoint startP, finishP;

    int x_bound_left, x_bound_right;
    int y_bound_lower, y_bound_upper;
    int x_dim, y_dim;

    QGraphicsScene *scene;

    QPen pen_black;
    QPen pen_red;
    QPen pen_green;

    QBrush brush;

};

#endif // GRAPHICS_H
