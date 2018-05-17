#include "paintwidget.h"
#include<cmath>

void PaintWidget :: rotate(int p1, int p2, int p3, int p4)
{
    if (Shape_Type == shape :: polygon)
    {
        int xmin = 9999, xmax = -9999, ymin = 9999, ymax = -9999;
        foreach (QPoint p, Shape->PointList)
        {
            if (p.x() < xmin) xmin = p.x();
            if (p.x() > xmax) xmax = p.x();
            if (p.y() < ymin) ymin = p.y();
            if (p.y() > ymax) ymax = p.y();
        }
        double xr = (double)(xmin + xmax) / 2;
        double yr = (double)(ymin + ymax) / 2;
        QList<QPoint> result;
        foreach (QPoint p, Shape->PointList)
        {
            double pi = 3.14159265;
            double x = xr + p1 * cos(pi / 6) * (p.x() - xr) + p2 * sin(pi / 6) * (p.y() - yr);
            double y = yr + p3 * sin(pi / 6) * (p.x() - xr) + p4 * cos(pi / 6) * (p.y() - yr);
            p.setX((int)x);
            p.setY((int)y);
            result.append(p);
        }
        Shape->PointList.clear();
        foreach (QPoint p, result)
            Shape->PointList.append(p);
        if (Shape->colorPoint.length() != 0) fill = true;
        Shape->colorPoint.clear();
        update();
    }
    else
    if (Shape_Type == shape :: line)
    {
        int xs = Shape->startPoint().x(), ys = Shape->startPoint().y();
        int xe = Shape->endPoint().x(), ye = Shape->endPoint().y();

        double xr = (double)(xs + xe) / 2, yr = (double)(ys + ye) / 2;

        double pi = 3.14159265;
        double startx = xr + p1 * cos(pi / 6) * (xs - xr) + p2 * sin(pi / 6) * (ys - yr);
        double starty = yr + p3 * sin(pi / 6) * (xs - xr) + p4 * cos(pi / 6) * (ys - yr);
        double endx = xr + p1 * cos(pi / 6) * (xe - xr) + p2 * sin(pi / 6) * (ye - yr);
        double endy = yr + p3 * sin(pi / 6) * (xe - xr) + p4 * cos(pi / 6) * (ye - yr);

        QPoint result_s, result_e;

        result_s.setX((int)startx);
        result_s.setY((int)starty);
        result_e.setX((int)endx);
        result_e.setY((int)endy);

        Shape->Start(result_s);
        Shape->End(result_e);

        update();
    }
}
