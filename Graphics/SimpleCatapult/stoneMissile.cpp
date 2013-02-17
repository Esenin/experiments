#include "stoneMissile.h"

StoneMissile::StoneMissile() :
    visualPlace(QRectF(-16, -16, 32, 32)),
    nuclearPayload(QRectF(-8, -8, 16, 16))
{
    //setFlag(ItemIsMovable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF StoneMissile::boundingRect() const
{
    return visualPlace;
}

QPainterPath StoneMissile::shape() const
{
    QPainterPath detonator;
    detonator.addEllipse(nuclearPayload);
    return detonator;
}

void StoneMissile::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon knife;
    knife.push_back(QPoint(0, 0));
    knife.push_back(QPoint(12, -16));
    knife.push_back(QPoint(0, -8));

    painter->save();
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);

    for (int i = 0; i < 4; i++)
    {
        painter->drawPolygon(knife);
        painter->rotate(90);
    }

    //skin
    painter->restore();
    painter->setBrush(Qt::black);
    painter->setPen(QPen(Qt::darkGray, 2));
    painter->drawEllipse(nuclearPayload);
}
