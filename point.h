#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(double x, double y);

    double x();
    double y();

    void setX(double x);
    void setY(double y);

private:
    double m_x, m_y;
};

#endif // POINT_H
