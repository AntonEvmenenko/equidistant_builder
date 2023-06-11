#ifndef SECTOR_H
#define SECTOR_H

#include "point.h"
#include "arc.h"

class Sector
{
public:
    Sector();
    Sector(Arc a);

    bool onEdge(Point p);
    bool inside(Point p);

private:
    Arc m_arc;
};

#endif // SECTOR_H
