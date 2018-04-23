#include "paintwidget.h"
#include <QMouseEvent>

PaintWidget :: PaintWidget(QWidget *parent) : QWidget(parent),
               Shape_Type(shape :: line), Shape(NULL), painted(true), pix_cannot(true),
               s_Point(false), s_Start(false), s_End(false)
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

void PaintWidget :: ClearScreen()
{
    shapeList.clear();
    Shape = NULL;
    painted = false;
    s_Point = false;
    s_Start = false;
    s_End = false;
    solid = false;
    pix_cannot = true;
    update();
}
