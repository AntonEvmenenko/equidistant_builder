#include "solver.h"

#include <QSet>
#include <QDebug>
#include <QtAlgorithms>

#include "geometry.h"

Solver::Solver()
{

}

void Solver::addPathPart(Segment segment)
{
    m_originalPath.append(PathPart(segment));
}

void Solver::addPathPart(Arc arc)
{
    m_originalPath.append(PathPart(arc));
}

QVector<PathPart>& Solver::getOriginalPath()
{
    return m_originalPath;
}

QVector<PathPart> Solver::getOffsettedPath()
{
    return m_offsetedPath;
}

QVector<PathPart> Solver::getSplittedPath()
{
    return m_splittedPath;
}

QVector<PathPart> Solver::getCutoffedPath()
{
    return m_cutoffedPath;
}

QVector<PathPart> Solver::offsetPathPart(PathPart pathPart)
{
    QVector<PathPart> result;

    if (pathPart.type() == PathPartType::Segment) {
        Vector n = Vector(pathPart.segment().a(), pathPart.segment().b()).rotate90CW().normalize();

        m_offsetedPath.append(PathPart(Segment(pathPart.segment().a() + n * m_offset, pathPart.segment().b() + n * m_offset)));
        m_offsetedPath.append(PathPart(Segment(pathPart.segment().a() + n * -m_offset, pathPart.segment().b() + n * -m_offset)));

        Point a = pathPart.segment().a();
        Point b = pathPart.segment().b();

        Vector ab_2 = Vector(a, b) * 0.5;
        m_cutoffRectangles.append(Rectangle(a + ab_2, ab_2, ab_2.rotate90CCW().normalize() * m_offset));
    } else if (pathPart.type() == PathPartType::Arc) {
        Vector n1 = Vector(pathPart.arc().a(), pathPart.arc().center()).normalize();
        Vector n2 = Vector(pathPart.arc().b(), pathPart.arc().center()).normalize();

        Arc out = Arc(pathPart.arc().a() + n1 * -m_offset, pathPart.arc().b() + n2 * -m_offset, pathPart.arc().center(), pathPart.arc().arcDirection());
        m_offsetedPath.append(PathPart(out));

        if (m_offset < pathPart.arc().radius() && !equal(m_offset, pathPart.arc().radius())) {
            Arc in = Arc(pathPart.arc().a() + n1 * m_offset, pathPart.arc().b() + n2 * m_offset, pathPart.arc().center(), pathPart.arc().arcDirection());
            m_offsetedPath.append(PathPart(in));

            m_cutoffClippedSectors.append(ClippedSector(in, out));
        } else {
            m_cutoffSectors.append(Sector(out));
        }
    }

    return result;
}

void Solver::makeOffset()
{
    for (auto i = m_originalPath.begin(); i != m_originalPath.end(); ++i) {
        QVector<PathPart> offset = offsetPathPart(*i);
        m_offsetedPath.append(offset);
    }
}

void Solver::addCircles()
{
    for (auto i = m_originalPath.begin(); i != m_originalPath.end(); ++i) {
        if (i->type() == PathPartType::Segment) {
            Circle c = Circle(i->segment().a(), m_offset);
            m_offsetedPath.append(PathPart(c));
            m_cutoffCircles.append(c);
        } else if (i->type() == PathPartType::Arc) {
            Circle c = Circle(i->arc().a(), m_offset);
            m_offsetedPath.append(PathPart(c));
            m_cutoffCircles.append(c);
        }
    }

    if (m_originalPath.last().type() == PathPartType::Segment) {
        Circle c = Circle(m_originalPath.last().segment().b(), m_offset);
        m_offsetedPath.append(PathPart(c));
        m_cutoffCircles.append(c);
    } else if (m_originalPath.last().type() == PathPartType::Arc) {
        Circle c = Circle(m_originalPath.last().arc().b(), m_offset);
        m_offsetedPath.append(PathPart(c));
        m_cutoffCircles.append(c);
    }
}

void Solver::split()
{
    for (int i = 0; i < m_offsetedPath.size(); ++i) {
        QVector<Point> intersectionPoints;
        for (int j = 0; j < m_offsetedPath.size(); ++j) {
            if (i != j) {
                QVector<Point> temp = getIntersectionPoints(m_offsetedPath[i], m_offsetedPath[j]);
                for (auto p = temp.begin(); p != temp.end(); ++p) {
                    intersectionPoints.append(*p);
                }
            }
        }

        removeEqualPoints(intersectionPoints);

        if (!intersectionPoints.isEmpty()) {
            m_splittedPath.append(split(m_offsetedPath[i], intersectionPoints));
        } else {
            m_splittedPath.append(m_offsetedPath[i]);
        }
    }
}

void Solver::cutoff()
{
    m_cutoffedPath = m_splittedPath;

    auto i = m_cutoffedPath.begin();

    while (i != m_cutoffedPath.end()) {
        bool needToCutoff = false;
        if (i->type() == PathPartType::Segment) {
            for (auto j = m_cutoffRectangles.begin(); j != m_cutoffRectangles.end(); ++j) {
                if (segmentInsideRectangle(i->segment(), *j)) {
                    needToCutoff = true;
                    break;
                }
            }
            if (!needToCutoff) {
                for (auto j = m_cutoffCircles.begin(); j != m_cutoffCircles.end(); ++j) {
                    if (segmentInsideCircle(i->segment(), *j)) {
                        needToCutoff = true;
                        break;
                    }
                }
            }
            if (!needToCutoff) {
                for (auto j = m_cutoffClippedSectors.begin(); j != m_cutoffClippedSectors.end(); ++j) {
                    if (segmentInsideClippedSector(i->segment(), *j)) {
                        needToCutoff = true;
                        break;
                    }
                }
            }
            if (!needToCutoff) {
                for (auto j = m_cutoffSectors.begin(); j != m_cutoffSectors.end(); ++j) {
                    if (segmentInsideSector(i->segment(), *j)) {
                        needToCutoff = true;
                        break;
                    }
                }
            }
        } else if (i->type() == PathPartType::Arc) {
            for (auto j = m_cutoffRectangles.begin(); j != m_cutoffRectangles.end(); ++j) {
                if (arcInsideRectangle(i->arc(), *j)) {
                    needToCutoff = true;
                    break;
                }
            }
            if (!needToCutoff) {
                for (auto j = m_cutoffCircles.begin(); j != m_cutoffCircles.end(); ++j) {
                    if (arcInsideCircle(i->arc(), *j)) {
                        needToCutoff = true;
                        break;
                    }
                }
            }
            if (!needToCutoff) {
                for (auto j = m_cutoffClippedSectors.begin(); j != m_cutoffClippedSectors.end(); ++j) {
                    if (arcInsideClippedSector(i->arc(), *j)) {
                        needToCutoff = true;
                        break;
                    }
                }
            }
            if (!needToCutoff) {
                for (auto j = m_cutoffSectors.begin(); j != m_cutoffSectors.end(); ++j) {
                    if (arcInsideSector(i->arc(), *j)) {
                        needToCutoff = true;
                        break;
                    }
                }
            }
        }
        if (needToCutoff) {
            i = m_cutoffedPath.erase(i);
        } else {
            ++i;
        }
    }
}

int Solver::getOffset()
{
    return m_offset;
}

void Solver::setOffset(int offset)
{
    m_offset = offset;
}

void Solver::solve()
{
    if (m_originalPath.empty()) {
        return;
    }

    makeOffset();
    addCircles();
    split();
    cutoff();
}

void Solver::clear()
{
    m_offsetedPath.clear();
    m_splittedPath.clear();
    m_cutoffedPath.clear();
    m_cutoffRectangles.clear();
    m_cutoffCircles.clear();
    m_cutoffClippedSectors.clear();
    m_cutoffSectors.clear();
}

QVector<Point> Solver::getIntersectionPoints(PathPart a, PathPart b)
{
    QVector<Point> result;

    if (a.type() == PathPartType::Segment && b.type() == PathPartType::Segment) {
        result = intersectionSegmentSegment(a.segment(), b.segment());
    } else if (a.type() == PathPartType::Segment && b.type() == PathPartType::Arc) {
        result = intersectionSegmentArc(a.segment(), b.arc());
    } else if (a.type() == PathPartType::Arc && b.type() == PathPartType::Segment) {
        result = intersectionSegmentArc(b.segment(), a.arc());
    } else if (a.type() == PathPartType::Segment && b.type() == PathPartType::Circle) {
        result = intersectionSegmentCircle(a.segment(), b.circle());
    } else if (a.type() == PathPartType::Circle && b.type() == PathPartType::Segment) {
        result = intersectionSegmentCircle(b.segment(), a.circle());
    } else if (a.type() == PathPartType::Arc && b.type() == PathPartType::Arc) {
        result = intersectionArcArc(a.arc(), b.arc());
    } else if (a.type() == PathPartType::Arc && b.type() == PathPartType::Circle) {
        result = intersectionArcCircle(a.arc(), b.circle());
    } else if (a.type() == PathPartType::Circle && b.type() == PathPartType::Arc) {
        result = intersectionArcCircle(b.arc(), a.circle());
    } else if (a.type() == PathPartType::Circle && b.type() == PathPartType::Circle) {
        result = intersectionCircleCircle(a.circle(), b.circle());
    }

    return result;
}

QVector<PathPart> Solver::split(PathPart pathPart, QVector<Point> points)
{
    Q_ASSERT(!points.isEmpty());

    QVector<PathPart> result;

    if (pathPart.type() == PathPartType::Segment) {
        result = splitSegment(pathPart.segment(), points);
    } else if (pathPart.type() == PathPartType::Arc) {
        result = splitArc(pathPart.arc(), points);
    } else if (pathPart.type() == PathPartType::Circle) {
        result = splitCircle(pathPart.circle(), points);
    }

    return result;
}

QVector<PathPart> Solver::splitSegment(Segment s, QVector<Point> points)
{
    Q_ASSERT(!points.isEmpty());

    QVector<PathPart> result;

    points.append(s.a());
    points.append(s.b());

    removeEqualPoints(points);

    Point a = s.a();

    std::sort(points.begin(), points.end(), [a](const Point &p1, const Point &p2){
       return Vector(a, p1).length() < Vector(a, p2).length();
    });

    for (int i = 0; i < points.size() - 1; ++i) {
        result.append(PathPart(Segment(points[i], points[i + 1])));
    }

    return result;
}

QVector<PathPart> Solver::splitArc(Arc a, QVector<Point> points)
{
    // TODO: check

    Q_ASSERT(!points.isEmpty());

    QVector<PathPart> result;

    points.append(a.a());
    points.append(a.b());

    removeEqualPoints(points);

    Point center = a.center();
    double startAngle = atan2(a.a().y() - center.y(), a.a().x() - center.x());
    double endAngle = atan2(a.b().y() - center.y(), a.b().x() - center.x());

    if (a.arcDirection() == ArcDirection::CCW) {
        if (endAngle < startAngle) {
            endAngle += 2 * M_PI;
        }

        auto compare = [startAngle, center](const Point &p1, const Point &p2){
            auto calculateAngle = [startAngle, center](const Point &p){
                double angle = atan2(p.y() - center.y(), p.x() - center.x());
                if (angle < startAngle) {
                    angle += 2 * M_PI;
                }
                return angle;
            };

            return calculateAngle(p1) < calculateAngle(p2);
        };

        std::sort(points.begin(), points.end(), compare);

        for (int i = 0; i < points.size() - 1; ++i) {
            result.append(PathPart(Arc(points[i], points[i + 1], center, ArcDirection::CCW)));
        }
    } else {
        if (endAngle > startAngle) {
            endAngle -= 2 * M_PI;
        }

        auto compare = [startAngle, center](const Point &p1, const Point &p2){
            auto calculateAngle = [startAngle, center](const Point &p){
                double angle = atan2(p.y() - center.y(), p.x() - center.x());
                if (angle > startAngle) {
                    angle -= 2 * M_PI;
                }
                return angle;
            };

            return calculateAngle(p1) > calculateAngle(p2);
        };

        std::sort(points.begin(), points.end(), compare);

        for (int i = 0; i < points.size() - 1; ++i) {
            result.append(PathPart(Arc(points[i], points[i + 1], center, ArcDirection::CW)));
        }
    }

    return result;
}

QVector<PathPart> Solver::splitCircle(Circle c, QVector<Point> points)
{
    Q_ASSERT(!points.isEmpty());

    QVector<PathPart> result;

    Point center = c.center();

    std::sort(points.begin(), points.end(), [center](const Point &p1, const Point &p2){
        return atan2(p1.y() - center.y(), p1.x() - center.x()) < atan2(p2.y() - center.y(), p2.x() - center.x());
    });

    for (int i = 0; i < points.size() - 1; ++i) {
        result.append(PathPart(Arc(points[i], points[i + 1], center, ArcDirection::CCW)));
    }

    result.append(PathPart(Arc(points.last(), points.first(), center, ArcDirection::CCW)));

    return result;
}
