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
        //设置基准点
        double xf = (double)(xmin + xmax) / 2;
        double yf = (double)(ymin + ymax) / 2;
        QList<QPoint> result;
        //对图形上的每个点按基准点进行缩放并存入结果
        foreach (QPoint p, Shape->PointList)
        {
            QPoint t;
            t.setX((double)p.x() * multiple + xf * (1 - multiple));
            t.setY((double)p.y() * multiple + yf * (1 - multiple));
            result.append(t);
        }
        //清除原点集并将结果加入
        Shape->PointList.clear();
        foreach (QPoint p, result)
            Shape->PointList.append(p);
        Shape->colorPoint.clear();
        update();
    }
    else
    {
        QPoint result_s, result_e;
        //设置缩放的基准点
        double xf = (double)(Shape->startPoint().x() + Shape->endPoint().x()) / 2;
        double yf = (double)(Shape->startPoint().y() + Shape->endPoint().y()) / 2;
        //对端点按照基准点套用缩放公式并存入结果中
        result_s.setX((double)Shape->startPoint().x() * multiple + xf * (1 - multiple));
        result_s.setY((double)Shape->startPoint().y() * multiple + yf * (1 - multiple));

        result_e.setX((double)Shape->endPoint().x() * multiple + xf * (1 - multiple));
        result_e.setY((double)Shape->endPoint().y() * multiple + yf * (1 - multiple));
        //重新设置端点
        Shape->Start(result_s);
        Shape->End(result_e);
        update();
    }
}
