#include "arc.h"

#include "vector.h"
#include "line.h"

Arc::Arc()
{

}

Arc::Arc(Point a, Point b, Point c): m_a(a), m_b(b), m_c(c)
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

Point &Arc::c()
{
    return m_c;
}

Point Arc::center()
{
    Vector ab(m_a, m_b);
    Vector bc(m_b, m_c);

    Point p1 = m_a + (ab * 0.5);
    Point p2 = m_b + (bc * 0.5);

    Vector n1 = ab.rotate90CW().normalize();
    Vector n2 = bc.rotate90CW().normalize();

    Line l1(p1, n1);
    Line l2(p2, n2);

    // TODO: add checks for parallelism / coincidence
    return intersection(l1, l2);
}

double Arc::radius()
{
    return Vector(m_a, center()).length();
}
