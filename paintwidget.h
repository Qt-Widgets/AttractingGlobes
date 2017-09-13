#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

#include "circle.h"
#include "countingthread.h"


class PaintWidget : public QWidget
{
    Q_OBJECT
private:
    CountingThread MyThread;
    QMutex *mutex;
    std::list<Circle> *list;
    std::list<Circle>::iterator ball_it;
    QTimer *TimerUpdate;
    double update_time;
    bool left_pressed = false;
public:
    PaintWidget(int obj_num, double update_time_ms);
    ~PaintWidget();
    void AddRandomBall();
    void AddBallXY(int x, int y);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif //PAINTWIDGET_H
