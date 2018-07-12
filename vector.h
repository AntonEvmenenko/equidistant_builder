#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

class Vector
{
public:
    Vector();
    Vector(Point a, Point b);

    double length();

private:
    Point m_a;
    Point m_b;
};

#endif // VECTOR_H
