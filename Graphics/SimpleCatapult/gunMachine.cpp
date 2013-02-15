#include "gunMachine.h"

GunMachine::GunMachine() :
    newAngle(45)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF GunMachine::boundingRect() const
{
    QPointF topLeft(-15, -15);
    QPointF bottomRight(15, 15);
    return QRectF(topLeft, bottomRight);
}

void GunMachine::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::SolidLine);
    painter->setBrush(Qt::black);
    painter->rotate(qreal(- newAngle));
    painter->drawRect(-20, 5, 30, 10);



    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkBlue);
    painter->drawEllipse(-15, -5, 20, 20);
}

void GunMachine::setCannonAngle(int angle)
{
    newAngle = angle;
}
