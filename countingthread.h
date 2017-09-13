#ifndef COUNTINGTHREAD_H
#define COUNTINGTHREAD_H

#include "circle.h"
#include <QThread>
#include <cmath>
#include <QMutex>



class CountingThread : public QThread
{
    Q_OBJECT
public:
    void run();
    void SetUpdateTime(double t);
    void SetList(std::list<Circle> *list1);
    void SetMutex(QMutex *mutex_thread);
public slots:
    void TotalCounter();
signals:
    void finished();
private:
    std::list<Circle> *list;
    QMutex *mutex;
    double update_time;
};

#endif // COUNTINGTHREAD_H
