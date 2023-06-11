#ifndef CLIPPEDSECTOR_H
#define CLIPPEDSECTOR_H

#include "arc.h"

class ClippedSector
{
public:
    ClippedSector();
    ClippedSector(Arc inArc, Arc outArc);

    bool onEdge(Point p);
    bool inside(Point p);

private:
    Arc m_inArc;
    Arc m_outArc;
};

#endif // CLIPPEDSECTOR_H
