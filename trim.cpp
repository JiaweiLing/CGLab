#include"paintwidget.h"
#include<string.h>
double min(double x, double y)
{
    if (x < y) return x; else return y;
}
double max(double x, double y)
{
    if (x > y) return x; else return y;
}
void PaintWidget :: Liang_Barsky()
{
    double xw_min = min(windows_start.x(), windows_end.x());
    double xw_max = max(windows_start.x(), windows_end.x());
    double yw_min = min(windows_start.y(), windows_end.y());
    double yw_max = max(windows_start.y(), windows_end.y());

    double xs = Shape->startPoint().x(), ys = Shape->startPoint().y();
    double xe = Shape->endPoint().x(), ye = Shape->endPoint().y();

    double delta_x = xe - xs, delta_y = ye - ys;
    double p[5], q[5];
    p[1] = -delta_x, p[2] = delta_x, p[3] = -delta_y, p[4] = delta_y;
    q[1] = xs - xw_min, q[2] = xw_max - xs, q[3] = ys - yw_min, q[4] = yw_max - ys;

    if (delta_x == 0)
    {
        if (q[1] < 0 || q[2] < 0)
        {
            Shape = NULL;
            shapeList.removeLast();
            solid = false;
            return;
        }
    }
    if (delta_y == 0)
    {
        if (q[3] < 0 || q[4] < 0)
        {
            Shape = NULL;
            shapeList.removeLast();
            solid = false;
            return;
        }
    }
    int i;
    int out2in_cross = 0, in2out_cross = 0;
    double out2in[5], in2out[5];
    memset(in2out, 0, sizeof(in2out));
    memset(out2in, 0, sizeof(out2in));
    for (i = 1; i <= 4; i++)
    {
        if (p[i] != 0)
        {
            double u = q[i] / p[i];
            if (p[i] < 0)
            {
                out2in[out2in_cross] = u;
                out2in_cross++;
            }
            else
            {
                in2out[in2out_cross] = u;
                in2out_cross++;
            }
        }
    }

    double u1 = 0, u2 = 1;
    for (i = 0; i < out2in_cross; i++)
        u1 = max(u1, out2in[i]);
    for (i = 0; i < in2out_cross; i++)
        u2 = min(u2, in2out[i]);

    if (u1 > u2)
    {
        Shape = NULL;
        shapeList.removeLast();
        solid = false;
        return;
    }
    double xs_new = xs + u1 * delta_x;
    double ys_new = ys + u1 * delta_y;
    double xe_new = xs + u2 * delta_x;
    double ye_new = ys + u2 * delta_y;

    QPoint start_new, end_new;
    start_new.setX(xs_new);
    start_new.setY(ys_new);
    end_new.setX(xe_new);
    end_new.setY(ye_new);
    Shape->Start(start_new);
    Shape->End(end_new);
}
