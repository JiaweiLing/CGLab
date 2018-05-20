#include"paintwidget.h"
#include<iostream>
int min(int x, int y)
{
    if (x < y) return x; else return y;
}
int max(int x, int y)
{
    if (x > y) return x; else return y;
}
void PaintWidget :: scale(double multiple)
{
    if (Shape_Type == shape :: polygon)
    {
        int xmin = 9999, xmax = -9999;
        int ymin = 9999, ymax = -9999;
        foreach (QPoint p, Shape->PointList)
        {
            xmin = min(xmin, p.x()); xmax = max(xmax, p.x());
            ymin = min(ymin, p.y()); ymax = max(ymax, p.y());
        }
        double xf = (double)(xmin + xmax) / 2;
        double yf = (double)(ymin + ymax) / 2;
        QList<QPoint> result;
        foreach (QPoint p, Shape->PointList)
        {
            QPoint t;
            t.setX((double)p.x() * multiple + xf * (1 - multiple));
            t.setY((double)p.y() * multiple + yf * (1 - multiple));
            result.append(t);
        }
        Shape->PointList.clear();
        foreach (QPoint p, result)
            Shape->PointList.append(p);
        Shape->colorPoint.clear();
        update();
    }
    else
    {
        QPoint result_s, result_e;
        double xf = (double)(Shape->startPoint().x() + Shape->endPoint().x()) / 2;
        double yf = (double)(Shape->startPoint().y() + Shape->endPoint().y()) / 2;

        result_s.setX((double)Shape->startPoint().x() * multiple + xf * (1 - multiple));
        result_s.setY((double)Shape->startPoint().y() * multiple + yf * (1 - multiple));

        result_e.setX((double)Shape->endPoint().x() * multiple + xf * (1 - multiple));
        result_e.setY((double)Shape->endPoint().y() * multiple + yf * (1 - multiple));

        Shape->Start(result_s);
        Shape->End(result_e);
        update();
    }
}
