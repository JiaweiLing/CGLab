#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"

class ellipse : public shape
{
    public:
          ellipse();
          void paint(QPainter &painter);
};
#endif // ELLIPSE_H
