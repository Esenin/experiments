#include "enemyFace.h"

EnemyFace::EnemyFace() :
    viewDirectionAngle(rand() % 360)
{
    setCacheMode(ItemCoordinateCache);
    setZValue(-1);
    visualPlace = QRectF(-25, -25, 50, 50);
}

QRectF EnemyFace::boundingRect() const
{
    return visualPlace;
}

QPainterPath EnemyFace::shape() const
{
    QPainterPath area;
    area.addEllipse(visualPlace);
    return area;
}

void EnemyFace::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::DashLine);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(visualPlace);

    int angle = 45;
    QRect eye = QRect(5, -5, 15, 10);

    painter->setPen(Qt::SolidLine);
    painter->setBrush(Qt::red);

    painter->save();
    painter->rotate( - angle);
    painter->drawRect(eye);

    painter->rotate(- 2 * angle);
    painter->drawRect(eye);
    painter->restore();

    QPen smile = QPen(Qt::black, 3);
    painter->setPen(smile);
    painter->drawLine(-10, 15, 8, 12);
}

void EnemyFace::runIntoWall()
{
    viewDirectionAngle = (viewDirectionAngle + 180) % 360;
}

QPointF EnemyFace::getNextTranslation()
{
    const int stepSize = 5;
    const int sightDelta = 42;
    const qreal pi = 3.1415;

    QPointF shiftPoint = QPointF(0, 0);

    viewDirectionAngle += (qrand() % sightDelta) - (sightDelta / 2);
    viewDirectionAngle = viewDirectionAngle % 360;

    qreal inRadian = (pi * viewDirectionAngle) / 180;
    shiftPoint.setX(stepSize * cos(inRadian));
    shiftPoint.setY(stepSize * sin(inRadian));

    return shiftPoint;
}

