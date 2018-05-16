#include "paintwidget.h"
void PaintWidget :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt :: white);
    //画一个矩形变成画布
    painter.drawRect(0, 0, size().width(), size().height());
    //对图形的绘制进行设置
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
