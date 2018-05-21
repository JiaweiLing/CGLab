#include "paintwidget.h"
#include<cmath>
void PaintWidget :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt :: white);
    //画一个矩形变成画布
    painter.drawRect(0, 0, size().width(), size().height());
    //对图形的绘制进行设置
    if (trim)
    {
        double xs = windows_start.x(), ys = windows_start.y();
        double xe = windows_end.x(), ye = windows_end.y();
        painter.setPen(QColor(0, 255, 0));
        painter.drawRect(xs, ys, abs(xe - xs), abs(ye - ys));
    }
    foreach (shape *Shape, shapeList)
    {
        Shape->paint(painter);
    }
    if (Shape) Shape->paint(painter);
    if (Shape && fill && painted && Shape_Type == shape :: polygon)
    {
        painter.setPen(QColor(255, 0, 0));
        Shape->FillPolygon(painter);
        fill = false;
    }
}
