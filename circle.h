#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class circle : public shape
{
    public:
          circle();
          void paint(QPainter &painter);
};
#endif // CIRCLE_H
