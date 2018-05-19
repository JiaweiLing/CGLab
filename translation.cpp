#include"paintwidget.h"

void PaintWidget :: translation(int dx, int dy)
{
    if (Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse)
    {
        int xs, ys, xe, ye;
        xs = Shape->startPoint().x() + dx;
        ys = Shape->startPoint().y() + dy;
        xe = Shape->endPoint().x() + dx;
        ye = Shape->endPoint().y() + dy;

        QPoint result_s, result_e;
        result_s.setX(xs); result_s.setY(ys);
        result_e.setX(xe); result_e.setY(ye);

        Shape->Start(result_s);
        Shape->End(result_e);

        update();
    }
    else
    {
        QList<QPoint> result;
        foreach (QPoint p, Shape->PointList)
        {
            int x = p.x() + dx, y = p.y() + dy;

            QPoint t;
            t.setX(x); t.setY(y);
            result.append(t);
        }
        Shape->PointList.clear();
        foreach (QPoint p, result)
        {
            Shape->PointList.append(p);
        }

        QList<QPoint> result_color;
        foreach (QPoint p, Shape->colorPoint)
        {
            int x = p.x() + dx, y = p.y() + dy;

            QPoint t;
            t.setX(x); t.setY(y);
            result_color.append(t);
            Shape->colorPoint.removeFirst();
        }
        Shape->colorPoint.clear();
        foreach (QPoint p, result_color)
        {
            Shape->colorPoint.append(p);
        }
        update();
    }
}
