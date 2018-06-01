#include"paintwidget.h"

void PaintWidget :: translation(int dx, int dy)
{
    if (Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse)
    {
        int xs, ys, xe, ye;
        //将端点平移
        xs = Shape->startPoint().x() + dx;
        ys = Shape->startPoint().y() + dy;
        xe = Shape->endPoint().x() + dx;
        ye = Shape->endPoint().y() + dy;
        //并将其加入结果
        QPoint result_s, result_e;
        result_s.setX(xs); result_s.setY(ys);
        result_e.setX(xe); result_e.setY(ye);
        //重新设置坐标
        Shape->Start(result_s);
        Shape->End(result_e);

        update();
    }
    else
    {
        QList<QPoint> result;
        foreach (QPoint p, Shape->PointList)
        {
            //得出原坐标平移的结果
            int x = p.x() + dx, y = p.y() + dy;
            //将新坐标加入结果的坐标集
            QPoint t;
            t.setX(x); t.setY(y);
            result.append(t);
        }
        //在绘制新图形之前清除原图形点的坐标
        Shape->PointList.clear();
        //加入新坐标
        foreach (QPoint p, result)
        {
            Shape->PointList.append(p);
        }

        QList<QPoint> result_color;
        foreach (QPoint p, Shape->colorPoint)
        {
            //对填充的点也进行平移
            int x = p.x() + dx, y = p.y() + dy;
            //加入到表示结果的点集
            QPoint t;
            t.setX(x); t.setY(y);
            result_color.append(t);
            Shape->colorPoint.removeFirst();
        }
        //在绘制新填充图形之前清除原填充图形点的坐标
        Shape->colorPoint.clear();
        //加入新坐标
        foreach (QPoint p, result_color)
        {
            Shape->colorPoint.append(p);
        }
        update();
    }
}
