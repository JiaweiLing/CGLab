#include "bezier.h"
#include<string.h>
bezier :: bezier()
{}

void bezier :: FillPolygon(QPainter &painter)
{}

void bezier :: paint(QPainter &painter)
{
    QList<QPoint> result;
    painter.setPen(Qt :: blue);
    foreach (QPoint p, PointList)
    {
        painter.drawRect(p.x() - 2, p.y() - 2, 4, 4);
    }

    int num = 0;
    if ((num = PointList.length()) < 2) return;

    double x[100050];
    double y[100050];
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));

    double k = 0.0;
    int i, j;
    while (k <= 1)
    {
        for (i = 0; i < num - 1; i++)
        {
            x[i] = (1 - k) * PointList[i].x() + k * PointList[i + 1].x();
            y[i] = (1 - k) * PointList[i].y() + k * PointList[i + 1].y();
        }
        for (i = 2; i < num; i++)
            for (j = 0; j < num - i; j++)
            {
                x[j] = (1 - k) * x[j] + k * x[j + 1];
                y[j] = (1 - k) * y[j] + k * y[j + 1];
            }
        double x_result = x[0];
        double y_result = y[0];
        QPoint p;
        p.setX(x_result);
        p.setY(y_result);
        result.append(p);
        k = k + 0.001 / num;
    }
    foreach (QPoint p, result)
    {
        painter.drawPoint(p.x(), p.y());
    }
}
