#include"paintwidget.h"
#include<string.h>
double min(double x, double y)
{
    if (x < y) return x; else return y;
}
double max(double x, double y)
{
    if (x > y) return x; else return y;
}
void PaintWidget :: Liang_Barsky()
{
    //求裁剪窗口横纵坐标的最值
    double xw_min = min(windows_start.x(), windows_end.x());
    double xw_max = max(windows_start.x(), windows_end.x());
    double yw_min = min(windows_start.y(), windows_end.y());
    double yw_max = max(windows_start.y(), windows_end.y());
    //表示端点
    double xs = Shape->startPoint().x(), ys = Shape->startPoint().y();
    double xe = Shape->endPoint().x(), ye = Shape->endPoint().y();

    double delta_x = xe - xs, delta_y = ye - ys;
    //求四个p、q值
    double p[5], q[5];
    p[1] = -delta_x, p[2] = delta_x, p[3] = -delta_y, p[4] = delta_y;
    q[1] = xs - xw_min, q[2] = xw_max - xs, q[3] = ys - yw_min, q[4] = yw_max - ys;
    //若p = 0，且q < 0则舍弃该线段
    if (delta_x == 0)
    {
        if (q[1] < 0 || q[2] < 0)
        {
            Shape = NULL;
            shapeList.removeLast();
            solid = false;
            return;
        }
    }
    if (delta_y == 0)
    {
        if (q[3] < 0 || q[4] < 0)
        {
            Shape = NULL;
            shapeList.removeLast();
            solid = false;
            return;
        }
    }
    int i;
    int out2in_cross = 0, in2out_cross = 0;
    double out2in[5], in2out[5];
    //两个数组分别表示从延长线外部延伸到内部、从内部延伸到外部
    memset(in2out, 0, sizeof(in2out));
    memset(out2in, 0, sizeof(out2in));
    for (i = 1; i <= 4; i++)
    {
        if (p[i] != 0)//p非零时，计算线段与边界或延长线交点的u值
        {
            double u = q[i] / p[i];
            if (p[i] < 0)//若p < 0，则从外到内
            {
                out2in[out2in_cross] = u;
                out2in_cross++;
            }
            else//反之，则从内到外
            {
                in2out[in2out_cross] = u;
                in2out_cross++;
            }
        }
    }

    double u1 = 0, u2 = 1;//设置线段交点初始参数
    //计算u1和u2
    for (i = 0; i < out2in_cross; i++)
        u1 = max(u1, out2in[i]);
    for (i = 0; i < in2out_cross; i++)
        u2 = min(u2, in2out[i]);
    //若u1 > u2舍弃该线段
    if (u1 > u2)
    {
        Shape = NULL;
        shapeList.removeLast();
        solid = false;
        return;
    }
    //否则被裁剪线段的端点由u的两个值决定
    double xs_new = xs + u1 * delta_x;
    double ys_new = ys + u1 * delta_y;
    double xe_new = xs + u2 * delta_x;
    double ye_new = ys + u2 * delta_y;
    //设置新坐标
    QPoint start_new, end_new;
    start_new.setX(xs_new);
    start_new.setY(ys_new);
    end_new.setX(xe_new);
    end_new.setY(ye_new);
    Shape->Start(start_new);
    Shape->End(end_new);
}
void PaintWidget :: Sutherland_Hodgman()
{
    //定义4个边界为裁剪窗口的左右上下
    double border[4];
    border[0] = min(windows_start.x(), windows_end.x());
    border[1] = max(windows_start.x(), windows_end.x());
    border[2] = min(windows_start.y(), windows_end.y());
    border[3] = max(windows_start.y(), windows_end.y());

    int i;
    QList<QPoint> result;
    int size = Shape->PointList.length();
    //对左边界进行裁剪
    for (i = 0; i < size; i++)
    {
        //按顺时针取点, s为终止点, e为起始点
        QPoint s = Shape->PointList[i];
        QPoint e = Shape->PointList[(i - 1 + size) % size];
        //若起始点在外侧，终止点在内侧，保存交点和终止点
        if (s.x() >= border[0] && e.x() < border[0])
        {
            double cross = ((s.y() - e.y()) * 1.0) / (1.0 * (s.x() - e.x())) * (1.0 * (border[0] - e.x())) + 1.0 * e.y();
            QPoint ans;
            ans.setX(border[0]);
            ans.setY(cross);
            result.append(ans);
            result.append(s);
        }
        else
        //若起始点和终止点都在边界内侧，保存终止点
        if (s.x() >= border[0] && e.x() >= border[0])
        {
            result.append(s);
        }
        else
        //若起始点在内侧，终止点在外侧，保存交点
        if (s.x() < border[0] && e.x() >= border[0])
        {
            double cross = ((s.y() - e.y()) * 1.0) / (1.0 * (s.x() - e.x())) * (1.0 * (border[0] - e.x())) + 1.0 * e.y();
            QPoint ans;
            ans.setX(border[0]);
            ans.setY(cross);
            result.append(ans);
        }
    }
    //将原点集清空并加入新点集
    Shape->PointList.clear();
    foreach(QPoint p, result)
    {
        QPoint temp = p;
        Shape->PointList.append(temp);
    }
    result.clear();
    //对右边界进行裁剪o
    size = Shape->PointList.length();
    for (i = 0; i < size; i++)
    {
        //按顺时针取点, s为终止点, e为起始点
        QPoint s = Shape->PointList[i];
        QPoint e = Shape->PointList[(i - 1 + size) % size];
        //若起始点在外侧，终止点在内侧，保存交点和终止点
        if (s.x() <= border[1] && e.x() > border[1])
        {
            double cross = ((s.y() - e.y()) * 1.0) / (1.0 * (s.x() - e.x())) * (1.0 * (border[1] - e.x())) + 1.0 * e.y();
            QPoint ans;
            ans.setX(border[1]);
            ans.setY(cross);
            result.append(ans);
            result.append(s);
        }
        else
        //若起始点和终止点都在边界内侧，保存终止点
        if (s.x() <= border[1] && e.x() <= border[1])
        {
            result.append(s);
        }
        else
        //若起始点在内侧，终止点在外侧，保存交点
        if (s.x() > border[1] && e.x() <= border[1])
        {
            double cross = ((s.y() - e.y()) * 1.0) / (1.0 * (s.x() - e.x())) * (1.0 * (border[1] - e.x())) + 1.0 * e.y();
            QPoint ans;
            ans.setX(border[1]);
            ans.setY(cross);
            result.append(ans);
        }
    }
    //将原点集清空并加入新点集
    Shape->PointList.clear();
    foreach(QPoint p, result)
    {
        QPoint temp = p;
        Shape->PointList.append(temp);
    }
    result.clear();
    //对上边界进行裁剪
    size = Shape->PointList.length();
    for (i = 0; i < size; i++)
    {
        //按顺时针取点, s为终止点, e为起始点
        QPoint s = Shape->PointList[i];
        QPoint e = Shape->PointList[(i - 1 + size) % size];
        //若起始点在外侧，终止点在内侧，保存交点和终止点
        if (s.y() >= border[2] && e.y() < border[2])
        {
            double cross = (1.0 * (s.x() - e.x())) / ((s.y() - e.y()) * 1.0) * ((border[2] - e.y()) * 1.0) + e.x() * 1.0;
            QPoint ans;
            ans.setX(cross);
            ans.setY(border[2]);
            result.append(ans);
            result.append(s);
        }
        else
        //若起始点和终止点都在边界内侧，保存终止点
        if (s.y() >= border[2] && e.y() >= border[2])
        {
            result.append(s);
        }
        else
        //若起始点在内侧，终止点在外侧，保存交点
        if (s.y() < border[2] && e.y() >= border[2])
        {
            double cross = (1.0 * (s.x() - e.x())) / ((s.y() - e.y()) * 1.0) * ((border[2] - e.y()) * 1.0) + e.x() * 1.0;
            QPoint ans;
            ans.setX(cross);
            ans.setY(border[2]);
            result.append(ans);
        }
    }
    //将原点集清空并加入新点集
    Shape->PointList.clear();
    foreach(QPoint p, result)
    {
        QPoint temp = p;
        Shape->PointList.append(temp);
    }
    result.clear();
    //对下边界裁剪
    size = Shape->PointList.length();
    for (i = 0; i < size; i++)
    {
        //按顺时针取点, s为终止点, e为起始点
        QPoint s = Shape->PointList[i];
        QPoint e = Shape->PointList[(i - 1 + size) % size];
        //若起始点在外侧，终止点在内侧，保存交点和终止点
        if (s.y() <= border[3] && e.y() > border[3])
        {
            double cross = (1.0 * (s.x() - e.x())) / ((s.y() - e.y()) * 1.0) * ((border[3] - e.y()) * 1.0) + e.x() * 1.0;
            QPoint ans;
            ans.setX(cross);
            ans.setY(border[3]);
            result.append(ans);
            result.append(s);
        }
        else
        //若起始点和终止点都在边界内侧，保存终止点
        if (s.y() <= border[3] && e.y() <= border[3])
        {
            result.append(s);
        }
        else
        //若起始点在内侧，终止点在外侧，保存交点
        if (s.y() > border[3] && e.y() <= border[3])
        {
            double cross = (1.0 * (s.x() - e.x())) / ((s.y() - e.y()) * 1.0) * ((border[3] - e.y()) * 1.0) + e.x() * 1.0;
            QPoint ans;
            ans.setX(cross);
            ans.setY(border[3]);
            result.append(ans);
        }
    }
    //将原点集清空并加入新点集
    Shape->PointList.clear();
    foreach(QPoint p, result)
    {
        QPoint temp = p;
        Shape->PointList.append(temp);
    }
    result.clear();

    Shape->colorPoint.clear();
}
