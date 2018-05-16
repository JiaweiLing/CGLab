#include<cmath>
#include<cstdio>
#include "ellipse.h"

ellipse :: ellipse()
{

}

void ellipse :: FillPolygon(QPainter &painter)
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
    //设置画笔
    painter.setPen(QColor(160, 160, 160));
    painter.drawRect(start.x() - 2, start.y() - 2, 4, 4);
    painter.drawRect(end.x() - 2, end.y() - 2, 4, 4);
    //设置初始点
    int x0 = start.x(), y0 = start.y();
    int x1 = end.x(), y1 = end.y();
    //计算椭圆中心以及半长轴和半短轴
    int xc = (x0 + x1) / 2, yc = (y0 + y1) / 2;
    int a = abs(x0 - x1) / 2, b = abs(y0 - y1) / 2;
    int x = 0, y = b;
    //EllipsePlot以(xc, yc)绘制四分椭圆
    //EllipsePlot()利用三个对称性, 完成四个对称点的绘制
    EllipsePlot(xc, yc, x, y, painter);
    //计算区域1决策参数初值p1
    double p1 = b * b - a * a * b + a * a / 4;
    //循环
    while (2 * b * b * x < 2 * a * a * y)
    {
        if (p1 < 0)
            //若p1 < 0, 重新计算决策参数, 选择像素(x, y)
            p1 = p1 + 2 * b * b * x + b * b;
        else
        {
            //若p1 > 0, 重新计算决策参数, 选择像素(x, y - 1)
            p1 = p1 + 2 * b * b * x - 2 * a * a * y + b * b;
            y--;
        }
        x++;
        //绘制四分圆
        EllipsePlot(xc, yc, x, y, painter);
    }
    //double p2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    //计算区域2决策参数初值p2
    double p2 = 2 * (b * (x + 0.5) + a * (y - 1) - a * b);
    //循环直至纵坐标为0
    while (y != 0)
    {
        if (p2 < 0)
        {
            //若p2 < 0, 重新计算决策参数, 选择像素(x + 1, y)
            p2 = p2 + 2 * b * b * x - 2 * a * a * y + a * a;
            x++;
        }
        else
            //若p2 > 0, 重新计算决策参数, 选择像素(x, y)
            p2 = p2 - 2 * a * a * y + a * a;
        y--;
        //绘制四分圆
        EllipsePlot(xc, yc, x, y, painter);
    }
}
