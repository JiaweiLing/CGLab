#include "paintwidget.h"
#include <QMouseEvent>

void PaintWidget :: mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt :: LeftButton)
    {
        if (Shape_Type == shape :: polygon && solid)
        {
            int i;
            QPoint p = event->pos();
            for (i = 0; i < Shape->PointList.length(); i++)
            {
                if ((abs(Shape->PointList[i].x() - p.x()) <= 4)
                 && (abs(Shape->PointList[i].y() - p.y()) <= 4))
                {
                    PointIndex = i;
                    SelectPoint = true;
                    return;
                }
            }
        }
        else
        if ((Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse) && solid)
        {
            QPoint p = event->pos();
            if ((abs(Shape->startPoint().x() - p.x()) <= 4)
             && (abs(Shape->startPoint().y() - p.y()) <= 4))
            {
                s_Start = true;
                return;
            }
            else
            if ((abs(Shape->endPoint().x() - p.x()) <= 4)
             && (abs(Shape->endPoint().y() - p.y()) <= 4))
            {
                s_End = true;
                return;
            }
        }
        if (Shape_Type == shape :: line)
        {
            solid = true;
            Shape = new line;
        }
        else
        if (Shape_Type == shape :: circle)
        {
            solid = true;
            Shape = new circle;
        }
        if (Shape_Type == shape :: ellipse)
        {
            solid = true;
            Shape = new ellipse;
        }
        if (Shape_Type == shape :: polygon)
        {
            solid = true;
            if (painted)
            {
                painted = false;
                Shape = new polygon;
            }
            painted = false;
        }
        if (Shape != NULL && Shape_Type != shape :: polygon)
            Shape->Start(event->pos());
        else
        if (Shape != NULL && Shape_Type == shape :: polygon)
            Shape->add_Point(event->pos());
    }
    else
    if (event->button() == Qt :: RightButton)
    {
        if (Shape && Shape_Type == shape :: polygon)
        {
            fill = false;
            shapeList<<Shape;
            update();
            painted = true;
        }
    }
}

void PaintWidget :: mouseMoveEvent(QMouseEvent *event)
{
    if (SelectPoint && Shape_Type == shape :: polygon)
    {
        Shape->PointList.removeAt(PointIndex);
        Shape->PointList.insert(PointIndex, event->pos());
        Shape->colorPoint.clear();
        update();
    }
    else
    if (s_Start && (Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse))
    {
        Shape->Start(event->pos());
        update();
    }
    else
    if (s_End && (Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse))
    {
        Shape->End(event->pos());
        update();
    }
    else
    if (Shape_Type != shape :: polygon)
    {
        Shape->End(event->pos());
        update();
    }
}
void PaintWidget :: mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt :: LeftButton)
    {
        if (Shape)
        {
            if (SelectPoint && (Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse))
                SelectPoint = false;
            else
            if (s_Start && (Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse))
                s_Start = false;
            else
            if (s_End && (Shape_Type == shape :: line || Shape_Type == shape :: circle || Shape_Type == shape :: ellipse))
                s_End = false;
            else
            if (Shape_Type != shape :: polygon)
            {
                Shape->End(event->pos());
                shapeList << Shape;
                update();
            }
        }
    }
}
