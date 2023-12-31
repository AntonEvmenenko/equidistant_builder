#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

class Vector;

Vector operator*(const Vector &vector, double k);
Vector operator*(double k, const Vector &vector);
double operator*(const Vector &v1, const Vector &v2);
double operator^(const Vector &v1, const Vector &v2);

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
    Vector rotate90CCW();

private:
    double m_x;
    double m_y;
};

#endif // VECTOR_H
