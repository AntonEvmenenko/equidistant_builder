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

    void on_createButton_clicked();

    void on_clearButton_clicked();

    void on_offsetLineEdit_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    void drawPoint(Point point, int width, QColor color, QPainter *painter);
    void drawArc(Arc arc, int width, QColor color, QPainter *painter);
    void drawSegment(Segment segment, int width, QColor color, QPainter *painter);

    Point getLastPathPoint();
    Point translatePoint(Point p);

    Solver m_solver;
    Point* temp;
    QVector<Point*> m_dragPoints;
};

#endif // MAINWINDOW_H