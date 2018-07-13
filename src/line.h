#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "vector.h"

class Line;

Point intersection(Line l1, Line l2);
Point projectPointOnLine(Point p, Line l);

class Line
{
public:
    Line();
    Line(Point a, Point b);
    Line(Point a, Vector v);

    double a();
    double b();
    double c();

private:
    double m_a;
    double m_b;
    double m_c;
};

#endif // LINE_H
