#include "vector.h"
#include <math.h>

Vector operator*(const Vector &vector, double k)
{
    return Vector(vector.x() * k, vector.y() * k);
}

Vector operator*(double k, const Vector &vector)
{
    return vector * k;
}

double operator*(const Vector &v1, const Vector &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y();
}

double operator^(const Vector &v1, const Vector &v2)
{
    return v1.x() * v2.y() - v2.x() * v1.y();
}

Vector::Vector()
{

}

Vector::Vector(Point a, Point b): m_x(b.x() - a.x()), m_y(b.y() - a.y())
{

}

Vector::Vector(double x, double y): m_x(x), m_y(y) {

}

double Vector::length()
{
    return sqrt(m_x * m_x + m_y * m_y);
}

double Vector::x() const
{
    return m_x;
}

double Vector::y() const
{
    return m_y;
}

Vector Vector::normalize()
{
    return Vector(m_x / length(), m_y / length());
}

Vector Vector::rotate90CW()
{
    return Vector(m_y, -m_x);
}

Vector Vector::rotate90CCW()
{
    return Vector(-m_y, m_x);
}
