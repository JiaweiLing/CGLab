#include "polygon.h"
#include<cstdio>
#include<algorithm>
using namespace std;
int cmp(const node &a, const node &b)
{
    return a.x < b.x;
}
void polygon :: FillPolygon(QPainter &painter)
{
    if (colorPoint.length() != 0) return;
    int maxy = -9999, miny = 9999;
    int num = PointList.length();
    int i, j, k;
    for (i = 0; i < num; i++)
    {
        if (PointList[i].y() > maxy) maxy = PointList[i].y();
        if (PointList[i].y() < miny) miny = PointList[i].y();
    }
    for (i = 0;i < 1050; i++) NET[i].clear();//有序边表初始化
    AET.clear();//活化边表初始化
    for (i = 0; i < num; i++)
    {
        QPoint pa = PointList[i], pb = PointList[(i + 1) % num];
        if (pa.y() == pb.y()) continue;
        int ymin, ymax;
        if (pa.y() < pb.y()) ymin = pa.y(); else ymin = pb.y();
        if (pa.y() > pb.y()) ymax = pa.y(); else ymax = pb.y();//求该边最大y值
        double x;
        if (pa.y() > pb.y()) x = pb.x(); else x = pa.x();//求下端点的x坐标
        double dx = (double)(pa.x() - pb.x()) / (double)(pa.y() - pb.y());//求斜率倒数
        //将边加入有序边表
        node pNode;
        pNode.ymax = ymax;
        pNode.x = x;
        pNode.slope = dx;
        NET[ymin].append(pNode);
    }
    for (i = 0; i < maxy; i++)
    {
        for (j = 0; j < NET[i].length(); j++)
        {
            node pNode = NET[i][j];
            AET.append(pNode);//将对应的边插入活化边表
        }
        sort(AET.begin(), AET.end(), cmp);//将交点沿扫描线按横坐标值自左至右排列
        for (j = 0; j < AET.length(); j++)
        {
            if (AET[j].ymax == i)//删除ymax == yk的边
            {
                AET.removeAt(j);
                j--;
            }
        }
        int temp = 0;
        while (temp < AET.length())
        {
            int xa = AET[temp].x, xb;
            if (temp + 1 < AET.length()) xb = AET[temp + 1].x; else break;
            for (k = xa + 1; k <= xb; k++)//填充操作
            {
                painter.drawPoint(k, i);
                QPoint p;
                p.setX(k);
                p.setY(i);
                colorPoint.append(p);//把p点加入颜色点集以供后续处理
            }
            temp = temp + 2;
        }
        for (j = 0; j < AET.length(); j++)//加上斜率倒数求交点的x坐标
            AET[j].x = AET[j].x + AET[j].slope;
    }
}
