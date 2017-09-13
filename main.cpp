#include <QApplication>
#include "paintwidget.h"
#include "circle.h"

int main(int argc, char *argv[])
{
    int init_balls = 10;
    int update_ms = 10;
    QApplication a(argc, argv);
    PaintWidget wgt(init_balls, update_ms);
    wgt.setStyleSheet("background-color: white");
    wgt.showMaximized();
    return a.exec();
}

