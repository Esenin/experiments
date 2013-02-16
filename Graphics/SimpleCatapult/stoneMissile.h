#ifndef STONEMISSILE_H
#define STONEMISSILE_H

#include <QGraphicsItem>
#include <QPainter>

class StoneMissile : public QGraphicsItem
{
public:
    StoneMissile();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QRectF visualPlace;
    QRectF nuclearPayload;
};

#endif // STONEMISSILE_H
