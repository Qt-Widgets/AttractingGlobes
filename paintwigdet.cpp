#include <paintwidget.h>

PaintWidget::PaintWidget(int obj_num, double update_time_ms)
{
    update_time = update_time_ms;
    TimerUpdate = new QTimer;
    list = new std::list<Circle>();
    mutex = new QMutex;
    ball_it = list->end();
    int i = 0;
    while (i < obj_num)
    {
          QTime timer;
          timer.start ();
          for(;timer.elapsed() < update_time*5;) {}
          AddRandomBall();
          i++;
    }
    MyThread.SetUpdateTime(update_time);
    MyThread.SetList(list);
    MyThread.SetMutex(mutex);
    MyThread.start();
    connect(&MyThread, SIGNAL(finished()), this, SLOT(update()));
    connect(TimerUpdate, SIGNAL(timeout()), &MyThread, SLOT(TotalCounter()));
    TimerUpdate->start(update_time);
}

PaintWidget::~PaintWidget()
{
    delete TimerUpdate;
    delete list;
    delete mutex;
}

void PaintWidget::paintEvent(QPaintEvent * )
{
    if (!mutex->tryLock(100)) return;
    QPainter painter(this);
    painter.setBrush(Qt::green);
    std::list<Circle>::iterator it = list->begin();
    while (it != list->end())
    {
        painter.drawEllipse((*it).GetX(), (*it).GetY(), (*it).GetRadius(), (*it).GetRadius());
        ++it;
    }
    mutex->unlock();
}

void PaintWidget::AddRandomBall()
{
    Circle Ball;
    list->push_back(Ball);
    ball_it = list->end();
}

void PaintWidget::mousePressEvent(QMouseEvent * event)
{
    if (!mutex->tryLock(100)) return;
    if (event->button() == Qt::RightButton)
    {
        left_pressed = false;
        std::list<Circle>::iterator it = list->begin();
        while (it != list->end())
        {
            if ((abs((*it).GetX() - event->pos().x()) < (*it).GetRadius())
                    && ((abs((*it).GetY() - event->pos().y()) < (*it).GetRadius())))
            {
                list->erase(it);
                ball_it = list->end();
                mutex->unlock();
                return;
            }
            it++;
        }
        QPoint position = event->pos();
        AddBallXY(position.x(), position.y());
    }
    else if (event->button() == Qt::LeftButton)
    {
        left_pressed = true;
        std::list<Circle>::iterator it = list->begin();
        while (it != list->end())
        {
            if ((abs((*it).GetX() - event->pos().x()) < (*it).GetRadius())
                    && ((abs((*it).GetY() - event->pos().y()) < (*it).GetRadius())))
            {
                (*it).LockByMouse(true);
                ball_it = it;
                break;
            }
            ball_it = list->end();
            it++;
        }
    }
    mutex->unlock();
}

void PaintWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (!mutex->tryLock(100)) return;
    if (ball_it != list->end() && left_pressed) (*ball_it).SetXY(event->x(), event->y());
    mutex->unlock();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if (!mutex->tryLock(100)) return;
    if (event->button() == Qt::LeftButton)
    {
        left_pressed = false;
        if (ball_it != list->end())
        {
            (*ball_it).LockByMouse(false);
            ball_it = list->end();
        }
    }
    mutex->unlock();
}


void PaintWidget::AddBallXY(int x, int y)
{
    Circle Ball(x, y);
    list->push_back(Ball);
    ball_it = list->end();
}


