#include<cmath>
#include<cstdio>
#include "ellipse.h"

ellipse :: ellipse()
{

}

void EllipsePlot(int xc, int yc, int x, int y, QPainter &painter)
{
    painter.drawPoint(xc + x, yc + y);
    painter.drawPoint(xc - x, yc + y);
    painter.drawPoint(xc + x, yc - y);
    painter.drawPoint(xc - x, yc - y);
}
void ellipse :: paint(QPainter &painter)
{
    painter.setPen(QColor(160, 160, 160));
    painter.drawRect(start.x() - 2, start.y() - 2, 4, 4);
    painter.drawRect(end.x() - 2, end.y() - 2, 4, 4);
    
    int x0 = start.x(), y0 = start.y();
    int x1 = end.x(), y1 = end.y();
    
    int xc = (x0 + x1) / 2, yc = (y0 + y1) / 2;
    int a = abs(x0 - x1) / 2, b = abs(y0 - y1) / 2;
    int x = 0, y = b;
    EllipsePlot(xc, yc, x, y, painter);
    double p1 = b * b - a * a * b + a * a / 4;
    while (2 * b * b * x < 2 * a * a * y)
    {
        if (p1 < 0)
            p1 = p1 + 2 * b * b * x + b * b;
        else
        {
            p1 = p1 + 2 * b * b * x - 2 * a * a * y + b * b;
            y--;
        }
        x++;
        EllipsePlot(xc, yc, x, y, painter);
    }
    //double p2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    double p2 = 2 * (b * (x + 0.5) + a * (y - 1) - a * b);
    while (y != 0)
    {
        if (p2 < 0)
        {
            p2 = p2 + 2 * b * b * x - 2 * a * a * y + a * a;
            x++;
        }
        else
            p2 = p2 - 2 * a * a * y + a * a;
        y--;
        EllipsePlot(xc, yc, x, y, painter);
    }
}
