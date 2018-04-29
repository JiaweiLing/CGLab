#include "paintwidget.h"
#include <QMouseEvent>

void PaintWidget :: mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt :: LeftButton) //如果按下鼠标左键
    {
        if (solid) //如果对象实例化
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
        if (Shape_Type == shape :: line) //由选择的图形种类创建新的图形对象
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
        if (Shape != NULL) Shape->Start(event->pos());//如果图形不为空则以相对坐标开始
    }
}

void PaintWidget :: mouseMoveEvent(QMouseEvent *event)
{
    if (s_Start)
    {
        Shape->Start(event->pos());
        update();
    }
    else
    if (s_End)
    {
        Shape->End(event->pos());
        update();
    }
    else
    {
        Shape->End(event->pos());
        update();
    }
}
void PaintWidget :: mouseReleaseEvent(QMouseEvent *event)
{
    //若按下的是鼠标左键, 则对松开后的事件进行相关变量的改变
    if (event->button() == Qt :: LeftButton)
    {
        if (Shape)
        {
            if (s_Start) s_Start = false;
            else if (s_End) s_End = false;
            else
            {
                Shape->End(event->pos());
                shapeList << Shape;
                update();
            }
        }
    }
}
