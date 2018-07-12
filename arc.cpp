#include "arc.h"

#include "vector.h"

Arc::Arc()
{

}

Arc::Arc(Point a, Point b, Point center): m_a(a), m_b(b), m_center(center)
{

}

Point& Arc::a()
{
    return m_a;
}

Point &Arc::b()
{
    return m_b;
}

Point& Arc::center()
{
    return m_center;
}

double Arc::radius()
{
    return Vector(m_a, m_center).length();
}
