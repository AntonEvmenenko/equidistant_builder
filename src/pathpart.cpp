#include "pathpart.h"

PathPart::PathPart()
{

}

PathPart::PathPart(Segment segment): m_segment(segment), m_type(PathPartType::Segment)
{

}

PathPart::PathPart(Arc arc): m_arc(arc), m_type(PathPartType::Arc)
{

}

PathPart::PathPart(Circle circle): m_circle(circle), m_type(PathPartType::Circle)
{

}

PathPartType PathPart::type()
{
    return m_type;
}

Segment& PathPart::segment()
{
    return m_segment;
}

Arc& PathPart::arc()
{
    return m_arc;
}

Circle& PathPart::circle()
{
    return m_circle;
}
