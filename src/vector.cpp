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
