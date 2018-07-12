#ifndef PATHPART_H
#define PATHPART_H

#include "segment.h"
#include "arc.h"

enum class PathPartType
{
    Segment,
    Arc
};

class PathPart
{
public:
    PathPart();
    PathPart(Segment segment);
    PathPart(Arc arc);

    PathPartType type();
    Segment& segment();
    Arc& arc();

private:
    Segment m_segment;
    Arc m_arc;
    PathPartType m_type;
};

#endif // PATHPART_H
