#include "paintwidget.h"
#include<cmath>

void PaintWidget :: rotate(int p1, int p2, int p3, int p4)
{
    if (Shape_Type == shape :: polygon || Shape_Type == shape :: bezier || Shape_Type == shape :: bsample)
    {
        int xmin = 9999, xmax = -9999, ymin = 9999, ymax = -9999;
        foreach (QPoint p, Shape->PointList)
        {
            if (p.x() < xmin) xmin = p.x();
            if (p.x() > xmax) xmax = p.x();
            if (p.y() < ymin) ymin = p.y();
            if (p.y() > ymax) ymax = p.y();
        }
        //设置基准点为图形的中心
        double xr = (double)(xmin + xmax) / 2;
        double yr = (double)(ymin + ymax) / 2;
        QList<QPoint> result;
        foreach (QPoint p, Shape->PointList)
        {
            //对每个点旋转30°，其中顺时针参数为1, -1, 1, 1，逆时针为1, 1, -1, 1
            double pi = 3.14159265;
            double x = xr + p1 * cos(pi / 6) * (p.x() - xr) + p2 * sin(pi / 6) * (p.y() - yr);
            double y = yr + p3 * sin(pi / 6) * (p.x() - xr) + p4 * cos(pi / 6) * (p.y() - yr);
            p.setX((int)x);
            p.setY((int)y);
            result.append(p);
        }
        //清空原点集，并将结果加入
        Shape->PointList.clear();
        foreach (QPoint p, result)
            Shape->PointList.append(p);
        //判断是否为填充图形
        if (Shape->colorPoint.length() != 0) fill = true;
        Shape->colorPoint.clear();
        update();
    }
    else
    if (Shape_Type == shape :: line)
    {
        //存储端点
        int xs = Shape->startPoint().x(), ys = Shape->startPoint().y();
        int xe = Shape->endPoint().x(), ye = Shape->endPoint().y();
        //(xr, yr)为基准点
        double xr = (double)(xs + xe) / 2, yr = (double)(ys + ye) / 2;
        //将点旋转30°，其中顺时针参数为1, -1, 1, 1，逆时针为1, 1, -1, 1
        double pi = 3.14159265;
        double startx = xr + p1 * cos(pi / 6) * (xs - xr) + p2 * sin(pi / 6) * (ys - yr);
        double starty = yr + p3 * sin(pi / 6) * (xs - xr) + p4 * cos(pi / 6) * (ys - yr);
        double endx = xr + p1 * cos(pi / 6) * (xe - xr) + p2 * sin(pi / 6) * (ye - yr);
        double endy = yr + p3 * sin(pi / 6) * (xe - xr) + p4 * cos(pi / 6) * (ye - yr);
        //加入到结果中
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
