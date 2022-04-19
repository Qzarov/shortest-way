#include "graphics.h"
#include "ui_graphics.h"

Graphics::Graphics(QVector<RestrictedArea> ar, QWidget *parent) :
//Graphics::Graphics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graphics)
{
    areas = ar;

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    configTools();

    QGraphicsView view(scene);
    view.show();
}

Graphics::~Graphics()
{
    delete ui;
}


void Graphics::configTools()
{
    scene->setSceneRect(0,0,500,500);

    pen_red.setColor(Qt::red);
    pen_red.setWidth(3);

    pen_black.setColor(Qt::black);
    pen_black.setWidth(5);

    pen_green.setColor(Qt::green);
    pen_green.setWidth(5);

    brush.setColor(Qt::red);
    brush.setStyle(Qt::BrushStyle::Dense6Pattern);
}


void Graphics::drawGrid()
{
    QGraphicsTextItem* textItem;
    int x1=0,y1=0,x2=0,y2=500;
    for (int i = 0; i <= 500; i+=50) {
        textItem = new QGraphicsTextItem(QString::number(x1));
        textItem->setPos(x1, 0);
        scene->addItem(textItem);
        scene->addLine(x1,y1,x2,y2);
        x1+=50;
        x2+=50;
    }

    x1=0,y1=0,x2=500,y2=0;
    for (int i = 0; i <= 500; i+=50) {
        textItem = new QGraphicsTextItem(QString::number(y1));
        textItem->setPos(0, y1);
        scene->addItem(textItem);
        scene->addLine(x1,y1,x2,y2);
        y1+=50;
        y2+=50;
    }
}


void Graphics::setBoundaries(int x_l, int x_r, int y_l, int y_u)
{
    x_bound_left = x_l;
    x_bound_right = x_r;
    y_bound_lower = y_l;
    y_bound_upper = y_u;
}

void Graphics::setDimension(int x_d, int y_d)
{
    x_dim = x_d;
    y_dim = y_d;
}


void Graphics::setWayPoints(QPoint s, QPoint f)
{
    startP = s;
    finishP = f;
}


void Graphics::drawAreas()
{
    for (int i = 0; i < areas.size(); ++i) {
        if (areas[i].getType() == AreaType::Circle) {
            QPoint p = areas[i].getPoints()[0];
            double r = areas[i].getRadius();
            scene->addEllipse(p.rx()-r/2, p.ry()-r/2, r, r, pen_red, brush);

        } else if (areas[i].getType() == AreaType::Polygon) {
            QPolygon pol = QPolygon(areas[i].getPoints());
            scene->addPolygon(pol, pen_red, brush);
        }
    }
}


void Graphics::drawPoints(QVector<QPoint> vec)
{
    QGraphicsTextItem* textItem;
    int r = 5;

    for (int i = 0; i < vec.size(); ++i) {
        scene->addEllipse(vec[i].rx()-r/2, vec[i].ry()-r/2,
                          r, r, pen_green);
        int num = getPointNum(vec[i]);
        textItem = new QGraphicsTextItem(QString::number(num));
        textItem->setPos(vec[i].rx(), vec[i].ry()-20);
        scene->addItem(textItem);
    }
}


void Graphics::drawWay(QVector<QPoint> vec)
{
    drawPoints(vec);
}


void Graphics::drawAll()
{
    drawGrid();
    drawPoints({startP, finishP});
    drawAreas();
}


int Graphics::getPointNum(QPoint p)
{
    int scale = 50;
    return (p.rx() / scale) + (p.ry() / scale) * x_dim;
}
