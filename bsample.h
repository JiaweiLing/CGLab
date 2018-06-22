#ifndef BSAMPLE_H
#define BSAMPLE_H
#include "shape.h"

class bsample : public shape
{
    public:
          bsample();
          void paint(QPainter &painter);
          void FillPolygon(QPainter &painter);
};
#endif // BSAMPLE_H
