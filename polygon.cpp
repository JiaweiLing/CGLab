#include "polygon.h"
#include<cmath>
#include<cstdio>
#include<algorithm>

polygon :: polygon()
{

}

void polygon :: paint_line(QPainter &painter, QPoint start, QPoint end)
{
    int x0 = start.x(), x1 = end.x(), y0 = start.y(), y1 = end.y();
    int delta_x = abs(x1 - x0), delta_y = abs(y1 - y0);
    int add_x, add_y;
    //决定增量的方向
    if (x1 > x0) add_x = 1; else add_x = -1;
    if (y1 > y0) add_y = 1; else add_y = -1;
    if (delta_y == 0)
    {
        //如果直线斜率为0
        int xa = x0, ya = y0;
        for (xa = x0; (add_x == 1 ? xa <= x1 : xa >= x1); xa = xa + add_x)
        {
            painter.drawPoint(xa, ya);
        }
    }
    else
    if (delta_x == 0)
    {
        //如果直线垂直于x轴
        int xa = x0, ya = y0;
        for (ya = y0; (add_y == 1 ? ya <= x1 : ya >= x1); ya = ya + add_y)
        {
            painter.drawPoint(xa, ya);
        }
    }
    else
    if (delta_x >= delta_y)
    {
        //如果斜率绝对值小于1
        int e = -delta_x; //设置决策参数初值
        int xa = x0, ya = y0;
        for (xa = x0; (add_x == 1 ? xa <= x1 : xa >= x1); xa = xa + add_x)
        {
            painter.drawPoint(xa, ya); //画点(x_k, y_k)
            // 若决策参数e小于0, e = e + 2delta_y
            e = e + delta_y * 2;
            if (e > 0)
            {
                //使下一个要画的点纵坐标加1
                ya = ya + add_y;
                // 若e大于0, e = e + 2delta_y - 2delta_x
                e = e - delta_x * 2;
            }
        }
    }
    else
    {
        //如果斜率大于1
        int e = -delta_y; //设置决策参数初值
        int xa = x0, ya = y0;

        for (ya = y0; (add_y == 1 ? ya <= y1 : ya >= y1); ya = ya + add_y)
        {
            painter.drawPoint(xa, ya);
            // 若决策参数e小于0, e = e + 2delta_x
            e = e + delta_x * 2;
            if (e > 0)
            {
                xa = xa + add_x;
                // 若e大于0, e = e - 2delta_y + 2delta_x
                e = e - delta_y * 2;
            }
        }
    }
}
void polygon :: paint(QPainter &painter)
{
    painter.setPen(QColor(255, 0, 0));//设置画笔
    foreach (QPoint p, PointList)
    {
        painter.drawRect(p.x() - 2, p.y() - 2, 4, 4);
    }//设置端点
    int temp = 0;
    if ((temp = PointList.length()) < 2) return;
    int num = PointList.length();
    if (num < 3) return;//如果小于三条边就不算多边形了
    QPoint start = PointList[0], end = PointList[1];
    paint_line(painter, start, end);//头两个顶点的连线
    int i;
    for (i = 2; i < num; i++)
    {
        start = end; end = PointList[i];
        paint_line(painter, start, end);
    }//连接多边形各顶点
    start = end; end = PointList[0];
    paint_line(painter, start, end);//连接首尾，使之成为封闭图形
    foreach(QPoint p, colorPoint)
    {
        painter.drawPoint(p.x(), p.y());//将其画出来
    }
}
