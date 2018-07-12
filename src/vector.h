#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

class Vector;

Vector operator*(const Vector &vector, double k);
Vector operator*(double k, const Vector &vector);

class Vector
{
public:
    Vector();
    Vector(Point a, Point b);
    Vector(double x, double y);

    double length();

    double x() const;
    double y() const;

    Vector normalize();
    Vector rotate90CW();

private:
    double m_x;
    double m_y;
};

#endif // VECTOR_H
