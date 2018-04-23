#include "paintwidget.h"
void PaintWidget :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt :: white);
    painter.drawRect(0, 0, size().width(), size().height());

    if (!pix_cannot)
    {
        painter.drawPixmap(QPoint(0, 0), pixmap);
        return;
    }
    foreach (shape *Shape, shapeList)
    {
        Shape->paint(painter);
    }
    if (Shape) Shape->paint(painter);
}
