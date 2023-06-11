#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "solver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_addSegmentButton_clicked();
    void on_addArcButton_clicked();
    void on_offsetSlider_valueChanged(int value);

    void on_showEquidistantCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void drawPoint(Point point, int width, QColor color, QPainter *painter);
    void drawArc(Arc arc, int width, QColor color, QPainter *painter);
    void drawSegment(Segment segment, int width, QColor color, QPainter *painter);
    void drawCircle(Circle circle, int width, QColor color, QPainter *painter);

    void drawPath(QVector<PathPart> path, int width, QColor color, QPainter *painter);

    void updateOffset(int offset);

    void repaint();

    Point getLastPathPoint();
    Point translatePoint(Point p);

    Solver m_solver;
    QVector<Point*> m_dragPoints;

    Point m_tempPoint;
    double m_angle = 0.0;

    bool m_showEquidistant = false;
};

#endif // MAINWINDOW_H
