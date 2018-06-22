#include "bsample.h"
#include<iostream>
#include<cstdio>
#include<cstring>

bsample :: bsample()
{}

void bsample :: FillPolygon(QPainter &painter)
{}

void bsample :: paint(QPainter &painter)
{
    QList<QPoint> result;
    painter.setPen(Qt :: yellow);
    foreach (QPoint p, PointList)
    {
        painter.drawRect(p.x() - 2, p.y() - 2, 4, 4);
    }
    if (PointList.length() < 3) return;
    int n_point = 1000;
    double delta = 1.0 / n_point;
    int i, j;
    for (i = 0; i < PointList.length() - 3; i++)
    {
        double x0 = (PointList[i].x() + 4 * PointList[i + 1].x() + PointList[i + 2].x()) / 6;
        double x1 = -(PointList[i].x() - PointList[i + 2].x()) / 2;
        double x2 = (PointList[i + 2].x() - 2 * PointList[i + 1].x() + PointList[i].x()) / 2;
        double x3 = -(PointList[i].x() - 3 * PointList[i + 1].x() + 3 * PointList[i + 2].x() - PointList[i + 3].x()) / 6;

        double y0 = (PointList[i].y() + 4 * PointList[i + 1].y() + PointList[i + 2].y()) / 6;
        double y1 = -(PointList[i].y() - PointList[i + 2].y()) / 2;
        double y2 = (PointList[i + 2].y() - 2 * PointList[i + 1].y() + PointList[i].y()) / 2;
        double y3 = -(PointList[i].y() - 3 * PointList[i + 1].y() + 3 * PointList[i + 2].y() - PointList[i + 3].y()) / 6;

        for (j = 0; j < n_point; j++)
        {
            double t1 = j * delta;
            double t2 = t1 * t1;
            double t3 = t1 * t1 * t1;

            double x = x0 + x1 * t1 + x2 * t2 + x3 * t3;
            double y = y0 + y1 * t1 + y2 * t2 + y3 * t3;

            QPoint p;
            p.setX(x);
            p.setY(y);
            result.append(p);
        }
    }
    foreach (QPoint p, result)
    {
        painter.drawPoint(p.x(), p.y());
    }
}
