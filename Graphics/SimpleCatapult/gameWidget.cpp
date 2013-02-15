#include "gameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QGraphicsView(parent),
    timerIdentify(0),
    powerRate(50),
    angleRate(45)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-250, -150, 500, 300);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(500, 300);
    setWindowTitle("Catapult");

    GunMachine *catapult = new GunMachine;
    scene->addItem(catapult);
    catapult->setPos(-200, -100);

}


void GameWidget::shoot()
{
    const int timerFree = 0;
    const int fps = 42;
    if (timerIdentify == timerFree)
        timerIdentify = startTimer(fps);

    //create stone here
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    const int step = 5;
    switch (event->key())
    {
    case Qt::Key_Up:
    {
        setAnglePlus(step);
        break;
    }
    case Qt::Key_Down:
    {
        setAnglePlus(- step);
        break;
    }
    case Qt::Key_Left:
    {
        setPowerPlus(- step);
        break;
    }
    case Qt::Key_Right:
    {
        setAnglePlus(step);
        break;
    }
    case Qt::Key_Space:
    {
        shoot();
        break;
    }
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GameWidget::timerEvent(QTimerEvent *)
{
    // !!!

}

void GameWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF sceneRect = this->sceneRect();
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GameWidget::setPowerPlus(int delta)
{
    if (powerRate + delta < 5 || powerRate + delta > 100)
        return;

    emit powerChanged(delta);
    powerRate += delta;
}

void GameWidget::setAnglePlus(int delta)
{
    if (angleRate + delta < 5 || angleRate + delta > 85)
        return;
    emit angleChanged(delta);
    angleRate += delta;
}
