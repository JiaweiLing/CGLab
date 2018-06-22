#ifndef BEZIER_H
#define BEZIER_H
#include "shape.h"
class bezier : public shape
{
    public:
          bezier();
          void paint(QPainter &painter);
          void FillPolygon(QPainter &painter);
};
#endif // BEZIER_H
