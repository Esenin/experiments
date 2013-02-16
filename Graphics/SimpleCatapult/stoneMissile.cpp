#include "stoneMissile.h"

StoneMissile::StoneMissile() :
    visualPlace(QRectF(-15, -15, 30, 30)),
    nuclearPayload(QRectF(-7, -7, 14, 14))
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
//    painter->save();
//    QPolygon
//    for (int i = 0; i < 4; i++)
//    {

//    }


    //skin
    painter->restore();
    painter->setBrush(Qt::black);
    painter->drawEllipse(nuclearPayload);
}
