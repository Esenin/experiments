#ifndef GUNMACHINE_H
#define GUNMACHINE_H

#include <QGraphicsItem>
#include <QPainter>

class GameWidget;

class GunMachine : public QGraphicsItem
{
    ///Q_OBJECT
public:
    GunMachine();

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    
public slots:
    void setCannonAngle(int angle);

protected:
    int newAngle;

};

#endif // GUNMACHINE_H
