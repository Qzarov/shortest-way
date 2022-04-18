#include "shortestway.h"
#include "./ui_shortestway.h"

void ShortestWay::setCenterVisibility(bool flag)
{
    if (flag) {
        ui->center_lbl->show();
        ui->x_center_lbl->show();
        ui->y_center_lbl->show();
        ui->r_center_lbl->show();
        ui->x_center_lineEdit->show();
        ui->y_center_lineEdit->show();
        ui->r_center_lineEdit->show();
        ui->add_circle_Button->show();
    } else {
        ui->center_lbl->hide();
        ui->x_center_lbl->hide();
        ui->y_center_lbl->hide();
        ui->r_center_lbl->hide();
        ui->x_center_lineEdit->hide();
        ui->y_center_lineEdit->hide();
        ui->r_center_lineEdit->hide();
        ui->add_circle_Button->hide();
    }

}


void ShortestWay::setNewPVisibility(bool flag)
{
    if (flag) {
        ui->newP_lbl->show();
        ui->x_newP_lbl->show();
        ui->y_newP_lbl->show();
        ui->x_newP_lineEdit->show();
        ui->y_newP_lineEdit->show();
        ui->add_point_Button->show();
        ui->add_Polygon_Button->show();
    } else {
        ui->newP_lbl->hide();
        ui->x_newP_lbl->hide();
        ui->y_newP_lbl->hide();
        ui->x_newP_lineEdit->hide();
        ui->y_newP_lineEdit->hide();
        ui->add_point_Button->hide();
        ui->add_Polygon_Button->hide();
    }

}


ShortestWay::ShortestWay(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShortestWay)
{
    ui->setupUi(this);

    setCenterVisibility(true);
    setNewPVisibility(false);

    //ui->del_area_Button->hide();

}

ShortestWay::~ShortestWay()
{
    delete ui;
}


void ShortestWay::on_areaType_comboBox_currentIndexChanged(int index)
{
    QString area_type = ui->areaType_comboBox->currentText();
    if (area_type == "circle") {
        setCenterVisibility(true);
        setNewPVisibility(false);
    } if (area_type == "polygon") {
        setCenterVisibility(false);
        setNewPVisibility(true);
    }
}


void ShortestWay::on_add_circle_Button_clicked()
{
    int x = ui->x_center_lineEdit->text().toInt();
    int y = ui->y_center_lineEdit->text().toInt();
    double r = ui->r_center_lineEdit->text().toFloat();

    RestrictedArea new_area(QPoint(x, y), r);
    areas.push_back(new_area);
    new_area.writeInDebug();
    new_area.print();

}


void ShortestWay::on_add_point_Button_clicked()
{
    int x = ui->x_newP_lineEdit->text().toInt();
    int y = ui->y_newP_lineEdit->text().toInt();

    QPoint new_p(x, y);

    bool new_polyg = true;

    if (areas.size() == 0) {}
    else if (areas[areas.size() - 1].getType() == AreaType::Circle) {}
    else { new_polyg = false; }

    if (new_polyg) {
        RestrictedArea new_area(AreaType::Polygon);
        new_area.addPoint(new_p);
        areas.push_back(new_area);
        new_area.writeInDebug();
    } else {
        areas[areas.size() - 1].addPoint(new_p);
        areas[areas.size() - 1].writeInDebug();
    }
}


void ShortestWay::on_add_Polygon_Button_clicked()
{
    // points?
    areas.push_back(RestrictedArea(AreaType::Polygon));
}


void ShortestWay::on_paint_Button_clicked()
{
    window = new Graphics(areas, this);   

    int x_bound_left = ui->x_l_lineEdit->text().toInt();
    int x_bound_right = ui->x_r_lineEdit->text().toInt();
    int y_bound_lower = ui->y_l_lineEdit->text().toInt();
    int y_bound_upper = ui->y_r_lineEdit->text().toInt();

    int x_dim = ui->x_dim_lineEdit->text().toInt();
    int y_dim = ui->y_dim_lineEdit->text().toInt();
    window->setBoundaries(x_bound_left, x_bound_right, y_bound_lower, y_bound_upper);
    window->setDimension(x_dim, y_dim);

    QPoint s(ui->x_start_lineEdit->text().toInt(),
             ui->y_start_lineEdit->text().toInt());
    QPoint f(ui->x_finish_lineEdit->text().toInt(),
             ui->y_finish_lineEdit->text().toInt());
    graph = Graph(x_dim, y_dim, s, f);
    qDebug() << "Graph builded: " << x_dim << " " << y_dim
             << ", start: " << s.rx() << s.ry()
             << ", finish: " << f.rx() << f.ry();
    window->setWayPoints(s, f);

    window->drawAll();
    window->show();
}


//QVector<RestrictedArea> ShortestWay::getAreas(){ return areas; }
