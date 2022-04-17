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

    scene->addText("Hello, world!");
    scene->setSceneRect(0,0,500,500);

    drawGrid();


    printAreas();

    QGraphicsView view(scene);
    view.show();
}

Graphics::~Graphics()
{
    delete ui;
}


void Graphics::drawGrid()
{
    int x1=0,y1=0,x2=0,y2=500;
    for (int i = 0; i <= 500; i+=50) {
        scene->addLine(x1,y1,x2,y2);
        x1+=50;
        x2+=50;
    }

    x1=0,y1=0,x2=500,y2=0;
    for (int i = 0; i <= 500; i+=50) {
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

void Graphics::printAreas()
{
    for (int i = 0; i < areas.size(); ++i) {
        if (areas[i].getType() == AreaType::Circle) {
            QPoint p = areas[i].getPoints()[0];
            double r = areas[i].getRadius();
            scene->addEllipse(p.rx(), p.ry(), r, r);

        } else if (areas[i].getType() == AreaType::Polygon) {
            QPolygon pol = QPolygon(areas[i].getPoints());
            scene->addPolygon(pol);
        }


    }
}
