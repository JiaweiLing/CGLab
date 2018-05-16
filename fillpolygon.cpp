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
    for (i = 0;i < 1050; i++) NET[i].clear();
    AET.clear();
    for (i = 0; i < num; i++)
    {
        QPoint pa = PointList[i], pb = PointList[(i + 1) % num];
        if (pa.y() == pb.y()) continue;
        int ymin, ymax;
        if (pa.y() < pb.y()) ymin = pa.y(); else ymin = pb.y();
        if (pa.y() > pb.y()) ymax = pa.y(); else ymax = pb.y();
        double x;
        if (pa.y() > pb.y()) x = pb.x(); else x = pa.x();
        double dx = (double)(pa.x() - pb.x()) / (double)(pa.y() - pb.y());
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
            AET.append(pNode);
        }
        sort(AET.begin(), AET.end(), cmp);
        for (j = 0; j < AET.length(); j++)
        {
            if (AET[j].ymax == i)
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
            for (k = xa + 1; k <= xb; k++)
            {
                painter.drawPoint(k, i);
                QPoint p;
                p.setX(k);
                p.setY(i);
                colorPoint.append(p);
            }
            temp = temp + 2;
        }
        for (j = 0; j < AET.length(); j++)
            AET[j].x = AET[j].x + AET[j].slope;
    }
}
