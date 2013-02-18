#ifndef GUNMACHINE_H
#define GUNMACHINE_H

#include <QGraphicsItem>
#include <QPainter>
#include <math.h>


class GunMachine : public QGraphicsItem
{
public:
    GunMachine();

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setCannonAngle(int angle);
    QPoint getBulletExitPoint();


protected:
    int newAngle;
    QRectF visualPlace;
    QPoint bulletExitPoint;

};

#endif // GUNMACHINE_H
