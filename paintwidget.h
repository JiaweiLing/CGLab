#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include<QWidget>
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "bezier.h"
class PaintWidget : public QWidget
{
    Q_OBJECT
    public:
          explicit PaintWidget(QWidget *parent = 0);
          void rotate(int p1, int p2, int p3, int p4);
          void translation(int dx, int dy);
          void scale(double multiple);
          void Liang_Barsky();
          void Sutherland_Hodgman();
    public slots:
          void Choose_Current_Shape(shape :: Type shpa);
          void ClearScreen();
          void Fill_Polygon();
          void Clockwise();
          void CounterClockwise();
          void Up();
          void Down();
          void Left();
          void Right();
          void Enlarge();
          void Reduce();
          void Trim();
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
          QPoint windows_start, windows_end;
          bool trim;
};
#endif // PAINTWIDGET_H
