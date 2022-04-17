#include "graphics.h"
#include "ui_graphics.h"

//Graphics::Graphics(QVector<RestrictedArea>* ar, QWidget *parent) :
Graphics::Graphics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graphics)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    scene->addText("Hello, world!");

    QGraphicsView view(scene);
    view.show();
}

Graphics::~Graphics()
{
    delete ui;
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
    //for (int i = 0; i < areas->size(); ++i) {
        //areas[i];
    //}
}
