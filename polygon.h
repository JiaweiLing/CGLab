#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"
#include<QObject>
#include<QVector>

class polygon : public shape
{
    public:
          polygon();
          void paint(QPainter &painter);
          void paint_line(QPainter &painter, QPoint start, QPoint end);

};
#endif // POLYGON_H
