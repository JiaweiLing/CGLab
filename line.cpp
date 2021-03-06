#include"line.h"
#include<cmath>
#include<cstdio>

line :: line()
{

}

void line :: FillPolygon(QPainter &painter)
{

}
void line :: paint(QPainter &painter)
{
    //设置画笔
    painter.setPen(QColor(160, 160, 160));
    painter.drawRect(start.x() - 2, start.y() - 2, 4, 4);
    painter.drawRect(end.x() - 2, end.y() - 2, 4, 4);
    //设置初始点
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
