#include"line.h"
#include<cmath>
#include<cstdio>

line :: line()
{

}

void line :: paint(QPainter &painter)
{
    painter.setPen(QColor(160, 160, 160));
    painter.drawRect(start.x() - 2, start.y() - 2, 4, 4);
    painter.drawRect(end.x() - 2, end.y() - 2, 4, 4);
    int x0 = start.x(), x1 = end.x(), y0 = start.y(), y1 = end.y();
    int delta_x = abs(x1 - x0), delta_y = abs(y1 - y0);

    int add_x, add_y;
    if (x1 > x0) add_x = 1; else add_x = -1;
    if (y1 > y0) add_y = 1; else add_y = -1;
    if (delta_y == 0)
    {
        int xa = x0, ya = y0;
        for (xa = x0; (add_x == 1 ? xa <= x1 : xa >= x1); xa = xa + add_x)
        {
            painter.drawPoint(xa, ya);
        }
    }
    else
    if (delta_x == 0)
    {
        int xa = x0, ya = y0;
        for (ya = y0; (add_y == 1 ? ya <= x1 : ya >= x1); ya = ya + add_y)
        {
            painter.drawPoint(xa, ya);
        }
    }
    else
    if (delta_x >= delta_y)
    {
        int e = -delta_x;
        int xa = x0, ya = y0;
        for (xa = x0; (add_x == 1 ? xa <= x1 : xa >= x1); xa = xa + add_x)
        {
            painter.drawPoint(xa, ya);
            e = e + delta_y * 2;
            if (e > 0)
            {
                ya = ya + add_y;
                e = e - delta_x * 2;
            }
        }
    }
    else
    {
        int e = -delta_y;
        int xa = x0, ya = y0;

        for (ya = y0; (add_y == 1 ? ya <= y1 : ya >= y1); ya = ya + add_y)
        {
            painter.drawPoint(xa, ya);
            e = e + delta_x * 2;
            if (e > 0)
            {
                xa = xa + add_x;
                e = e - delta_y * 2;
            }
        }
    }
}
