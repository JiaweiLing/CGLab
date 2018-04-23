#include<cmath>
#include<cstdio>
#include "circle.h"

circle :: circle()
{

}

void PlotCircle(int xc, int yc, int x, int y, QPainter &painter)
{
    painter.drawPoint(xc + x, yc + y);
    painter.drawPoint(xc - x, yc + y);
    painter.drawPoint(xc + x, yc - y);
    painter.drawPoint(xc - x, yc - y);
    painter.drawPoint(xc + y, yc + x);
    painter.drawPoint(xc - y, yc + x);
    painter.drawPoint(xc + y, yc - x);
    painter.drawPoint(xc - y, yc - x);
}

void circle :: paint(QPainter &painter)
{
    painter.setPen(QColor(160, 160, 160));
    painter.drawRect(start.x() - 2, start.y() - 2, 4, 4);
    painter.drawRect(end.x() - 2, end.y() - 2, 4, 4);

    int x0 = start.x(), y0 = start.y();
    int x1 = end.x(), y1 = end.y();
    int xc = (x0 + x1) / 2, yc = (y0 + y1) / 2;
    int r = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)) / 2;
    int x = 0, y = r;
    PlotCircle(xc, yc, x, y, painter);

    int p = 1.25 - r;
    while (x < y)
    {
        if (p < 0)
            p = p + 2 * x + 3;
        else
        {
            p = p + 2 * x - 2 * y + 5;
            y--;
        }
        x++;
        PlotCircle(xc, yc, x, y, painter);
    }
}
