#ifndef LINE_H
#define LINE_H
#include "shape.h"
class line : public shape
{
    public:
            line();
            void paint(QPainter &painter);
};
#endif // LINE_H
