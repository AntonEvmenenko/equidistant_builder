#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

#define SEGMENT_WIDTH 3
#define SEGMENT_COLOR Qt::black

#define ARC_WIDTH 3
#define ARC_COLOR Qt::black

#define POINT_WIDTH 6
#define POINT_COLOR Qt::red

#define ARC_CENTER_WIDTH 6
#define ARC_CENTER_COLOR Qt::green

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QVector<PathPart>& path = m_solver.getPath();

    for (auto i = path.begin(); i < path.end(); ++i) {
        if (i->type() == PathPartType::Arc) {
            drawArc(i->arc(), ARC_WIDTH, ARC_COLOR, &painter);
        } else if (i->type() == PathPartType::Segment) {
            drawSegment(i->segment(), SEGMENT_WIDTH, SEGMENT_COLOR, &painter);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Point p = Point(event->x(), event->y());

    QVector<PathPart>& path = m_solver.getPath();

    const double eps = 5;

    for (auto i = path.begin(); i < path.end(); ++i) {
        if (i->type() == PathPartType::Segment) {
            if (Vector(p, i->segment().a()).length() < eps) {
                m_dragPoints.append(&(i->segment().a()));
            } else if (Vector(p, i->segment().b()).length() < eps) {
                m_dragPoints.append(&(i->segment().b()));
            }
        } else {
            if (Vector(p, i->arc().a()).length() < eps) {
                m_dragPoints.append(&(i->arc().a()));
            } else if (Vector(p, i->arc().b()).length() < eps) {
                m_dragPoints.append(&(i->arc().b()));
            } else if (Vector(p, i->arc().c()).length() < eps) {
                m_dragPoints.append(&(i->arc().c()));
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_dragPoints.clear();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_dragPoints.isEmpty()) {
        for (auto i = m_dragPoints.begin(); i != m_dragPoints.end(); ++i) {
            (*i)->setX(event->x());
            (*i)->setY(event->y());
        }
    }
    repaint();
}

void MainWindow::drawPoint(Point point, int width, QColor color, QPainter *painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    painter->drawPoint(QPointF(point.x(), point.y()));
}

void MainWindow::drawArc(Arc arc, int width, QColor color, QPainter* painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    double radius = arc.radius();
    QRectF rectangle(arc.center().x() - radius, arc.center().y() - radius, 2 * radius, 2 * radius);

    double startAngle = atan2(arc.c().y() - arc.center().y(), arc.c().x() - arc.center().x()) * 180. / M_PI;
    double endAngle = atan2(arc.a().y() - arc.center().y(), arc.a().x() - arc.center().x()) * 180. / M_PI;

    qDebug() << startAngle << endAngle;

    startAngle *= -16.;
    endAngle *= -16.;

    painter->drawArc(rectangle, startAngle, endAngle - startAngle);

    drawPoint(arc.a(), POINT_WIDTH, /*POINT_COLOR*/Qt::red, painter);
    drawPoint(arc.b(), POINT_WIDTH, /*POINT_COLOR*/Qt::green, painter);
    drawPoint(arc.c(), POINT_WIDTH, /*POINT_COLOR*/Qt::blue, painter);
    drawPoint(arc.center(), ARC_CENTER_WIDTH, ARC_CENTER_COLOR, painter);
}

void MainWindow::drawSegment(Segment segment, int width, QColor color, QPainter *painter)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    painter->setPen(pen);

    painter->drawLine(segment.a().x(), segment.a().y(), segment.b().x(), segment.b().y());

    drawPoint(segment.a(), POINT_WIDTH, POINT_COLOR, painter);
    drawPoint(segment.b(), POINT_WIDTH, POINT_COLOR, painter);
}

Point MainWindow::getLastPathPoint()
{
    if (m_solver.getPath().isEmpty()) {
        return Point(200, 200);
    }

    PathPart lastPathPart = m_solver.getPath().last();

    Point p;
    if (lastPathPart.type() == PathPartType::Segment) {
        p = lastPathPart.segment().b();
    } else {
        p = lastPathPart.arc().c();
    }

    return p;
}

void MainWindow::on_addSegmentButton_clicked()
{
    Point lastPoint = getLastPathPoint();

    m_solver.addPathPart(Segment(lastPoint, lastPoint + Vector(100, 0)));

    repaint();
}

void MainWindow::on_addArcButton_clicked()
{
    Point lastPoint = getLastPathPoint();

    m_solver.addPathPart(Arc(lastPoint, lastPoint + Vector(70, 0), lastPoint + Vector(70, 70)));

    repaint();
}
