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
