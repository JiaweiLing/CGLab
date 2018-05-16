#include<cmath>
#include<cstdio>
#include "circle.h"

circle :: circle()
{

}

void circle :: FillPolygon(QPainter &painter)
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
    //设置画笔
    painter.setPen(QColor(160, 160, 160));
    painter.drawRect(start.x() - 2, start.y() - 2, 4, 4);
    painter.drawRect(end.x() - 2, end.y() - 2, 4, 4);
    //设置初始点
    //并计算圆心(xc, yc), 半径r和圆周点(0, r)
    int x0 = start.x(), y0 = start.y();
    int x1 = end.x(), y1 = end.y();
    int xc = (x0 + x1) / 2, yc = (y0 + y1) / 2;
    int r = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)) / 2;
    int x = 0, y = r;
    //PlotCircle函数为画点函数
    //其以圆心(xc, yc), 绘制八分圆
    PlotCircle(xc, yc, x, y, painter);
    //计算初始决策参数值p
    double p = 1.25 - r;
    while (x < y) //若x < y开始循环
    {
        if (p < 0)
            //若p < 0, p = p + 2x + 1
            p = p + 2 * x + 3;
        else
        {
            //若p > 0, p = p + 2x + 1 - 2y
            p = p + 2 * x - 2 * y + 5;
            //选择像素位置(x, y - 1)
            y--;
        }
        x++;
        //绘制八分圆
        PlotCircle(xc, yc, x, y, painter);
    }
}
