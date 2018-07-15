#ifndef PATHPART_H
#define PATHPART_H

#include "segment.h"
#include "arc.h"
#include "circle.h"

enum class PathPartType
{
    Segment,
    Arc,
    Circle
};

class PathPart
{
public:
    PathPart();
    PathPart(Segment segment);
    PathPart(Arc arc);
    PathPart(Circle arc);

    PathPartType type();
    Segment& segment();
    Arc& arc();
    Circle& circle();

private:
    Segment m_segment;
    Arc m_arc;
    Circle m_circle;
    PathPartType m_type;
};

#endif // PATHPART_H
