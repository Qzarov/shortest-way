#ifndef SHORTESTWAY_H
#define SHORTESTWAY_H

#include <QMainWindow>
#include <QVector>
#include <QList>
#include <QString>

#include "func_classes.h"
#include "graphics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ShortestWay; }
QT_END_NAMESPACE

class ShortestWay : public QMainWindow
{
    Q_OBJECT

public:
    ShortestWay(QWidget *parent = nullptr);
    ~ShortestWay();

private slots:

    void on_areaType_comboBox_currentIndexChanged(int index);
    void on_add_circle_Button_clicked();
    void on_add_point_Button_clicked();
    void on_add_Polygon_Button_clicked();
    void on_paint_Button_clicked();

private:
    void setCenterVisibility(bool flag);
    void setNewPVisibility(bool flag);

    Ui::ShortestWay *ui;
    QVector<RestrictedArea> areas;

    //Graphics
    Graphics *window;



};
#endif // SHORTESTWAY_H
