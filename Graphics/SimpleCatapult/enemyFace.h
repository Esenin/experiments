#ifndef ENEMYFACE_H
#define ENEMYFACE_H

#include <QGraphicsItem>
#include <QPainter>
#include <math.h>

class EnemyFace : public QGraphicsItem
{
public:
    EnemyFace();
    
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPointF getNextTranslation();
    void runIntoWall();

protected:
    QRectF visualPlace;
    int viewDirectionAngle;
};

#endif // ENEMYFACE_H
