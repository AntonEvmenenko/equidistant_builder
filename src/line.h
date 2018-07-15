#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "vector.h"
#include "segment.h"

class Line;

Point projectPointOnLine(Point p, Line l);

class Line
{
public:
    Line();
    Line(Point a, Point b);
    Line(Point a, Vector v);
    Line(Segment s);

    double a();
    double b();
    double c();

    bool contains(Point p);

    Vector unitGuidingVector();

private:
    double m_a;
    double m_b;
    double m_c;
};

#endif // LINE_H
