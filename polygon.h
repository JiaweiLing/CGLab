#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"
#include<QObject>
#include<QVector>
struct node
{
    int ymax;
    double x;
    double slope;
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
