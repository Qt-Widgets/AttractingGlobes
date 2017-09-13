#include "circle.h"

Circle::Circle()
{
    qsrand(QTime::currentTime().msec());
    int min = 250;
    int max = 700;
    int randomx = (qrand()) % max + min;
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    min = 150;
    max = 450;
    int randomy = (qrand()) % max + min;
    x0 = randomx;
    y0 = randomy;
}

Circle::Circle(double x, double y)
{
    x0 = x;
    y0 = y;
}

Circle::Circle(double x, double y, double r)
{
    x0 = x;
    y0 = y;
    radius = r;
}

void Circle::SetXY(double x, double y)
{
    x0 = x;
    y0 = y;
}
double Circle::GetX()
{
    return x0;
}
double Circle::GetY()
{
    return y0;
}
void Circle::SetRadius(double r)
{
    radius = r;
}
double Circle::GetRadius()
{
    return radius;
}
double Circle::GetSpeedX()
{
    return speedX;
}
double Circle::GetSpeedY()
{
    return speedY;
}
void Circle::SetSpeedXY(double vx, double vy)
{
    speedX = vx;
    speedY = vy;
}
double Circle::GetMass()
{
    return mass;
}

void Circle::SetMass(double m)
{
    mass = m;
}

void Circle::SetForce(double fx, double fy)
{
    forceX = fx;
    forceY = fy;
}

double Circle::GetForceX()
{
    return forceX;
}

double Circle::GetForceY()
{
    return forceY;
}

void Circle::LockByMouse(bool b)
{
    locked = b;
}

bool Circle::IsLockedByMouse()
{
    return locked;
}
