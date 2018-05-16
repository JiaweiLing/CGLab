#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include<QWidget>
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
class PaintWidget : public QWidget
{
    Q_OBJECT
    public:
          explicit PaintWidget(QWidget *parent = 0);
    public slots:
          void Choose_Current_Shape(shape :: Type shpa);
          void ClearScreen();
          void Fill_Polygon();
    protected:
          void paintEvent(QPaintEvent *event);
          void mousePressEvent(QMouseEvent *event);
          void mouseMoveEvent(QMouseEvent *event);
          void mouseReleaseEvent(QMouseEvent *event);

    private:
          shape :: Type Shape_Type;
          shape *Shape;
          bool painted;
          bool s_Start;
          bool s_End;
          bool solid;
          QList<shape*> shapeList;
          int PointIndex;
          bool SelectPoint;
          bool fill;
};
#endif // PAINTWIDGET_H
