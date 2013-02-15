#include "gunMachine.h"

GunMachine::GunMachine() :
    newAngle(45)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    visualPlace = QRectF(-30, -40, 100, 100);
}

QRectF GunMachine::boundingRect() const
{
    return visualPlace;
}

void GunMachine::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->rotate(qreal(- newAngle));
    painter->setPen(Qt::SolidLine);
    painter->setBrush(Qt::black);

    painter->drawRect(-5, -8, 30, 16);

    painter->restore();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkBlue);
    painter->drawEllipse(-15, -15, 30, 30);

    painter->setBrush(QColor(49, 0, 98));
    painter->drawRect(-30, 10, 60, 25);

    QPolygonF baseTriangle;
    baseTriangle.push_back(QPointF(30, 10));
    baseTriangle.push_back(QPointF(30, 35));
    baseTriangle.push_back(QPointF(50, 10));
    painter->drawPolygon(baseTriangle);

}

void GunMachine::setCannonAngle(int angle)
{
    newAngle = angle;
    this->update();
}
