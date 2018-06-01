#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"
#include<QObject>
#include<QVector>
struct node
{
    int ymax;//记录最大y值
    double x;//记录下端点x坐标
    double slope;//记录边斜率的倒数
};
class polygon : public shape
{
    public:
          polygon();
          void paint(QPainter &painter);
          void paint_line(QPainter &painter, QPoint start, QPoint end);
          void FillPolygon(QPainter &painter);
    private:
          QList<node> NET[1050];
          QList<node> AET;

};
#endif // POLYGON_H
