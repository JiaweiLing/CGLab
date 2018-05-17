#include "paintwidget.h"
#include <QMouseEvent>

PaintWidget :: PaintWidget(QWidget *parent) : QWidget(parent),
               Shape_Type(shape :: line), Shape(NULL), painted(true),
               solid(false), SelectPoint(false), fill(false),
               s_Start(false), s_End(false)
{
    setMaximumSize(500, 500);
    setMinimumSize(500, 500);
}

void PaintWidget :: Choose_Current_Shape(shape :: Type shpa)
{
    if (shpa != Shape_Type)
    {
        Shape_Type = shpa;
        solid = false;
    }
}
//设置清屏操作导致的变量变化
void PaintWidget :: ClearScreen()
{
    shapeList.clear();
    Shape = NULL;
    painted = true;
    s_Start = false;
    s_End = false;
    solid = false;
    SelectPoint = false;
    fill = false;
    update();
}
void PaintWidget :: Fill_Polygon()
{
    fill = true;
    if (painted) update();
}

void PaintWidget :: Clockwise()
{
    rotate(1, -1, 1, 1);
}

void PaintWidget :: CounterClockwise()
{
    rotate(1, 1, -1, 1);
}
