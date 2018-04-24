#ifndef SHAPE_H
#define SHAPE_H
#include<QPoint>
#include<QPainter>

class shape
{
    public:
            enum Type{none, line, circle, ellipse};
            shape();
            void Start(QPoint s)
            {
                 start = s;
            }
            void End(QPoint e)
            {
                 end = e;
            }
            QPoint startPoint() { return start; }
            QPoint endPoint() { return end; }
            void virtual paint(QPainter & painter) = 0;
            QList<QPoint> PointList;
    protected:
            QPoint start;
            QPoint end;
};
#endif // SHAPE_H
