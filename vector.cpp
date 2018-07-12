#include "vector.h"
#include <math.h>


Vector::Vector()
{

}

Vector::Vector(Point a, Point b): m_a(a), m_b(b)
{

}

double Vector::length()
{
    return sqrt((m_b.x() - m_a.x()) * (m_b.x() - m_a.x()) + (m_b.y() - m_a.y()) * (m_b.y() - m_a.y()));
}
