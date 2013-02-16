#include "gameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QGraphicsView(parent),
    timerIdentify(0),
    powerRate(50),
    angleRate(45),
    readyToFire(true)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-250, -150, 500, 300);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(500, 300);
    setWindowTitle("Catapult");

    catapult = new GunMachine;
    scene->addItem(catapult);
    catapult->setPos(-200, 100);


    startRound();
}

GameWidget::~GameWidget()
{
    delete catapult;
    delete scene;
}

void GameWidget::startRound()
{
    createEnemy();

    const int timerFree = 0;
    const int fps = 42;
    if (timerIdentify == timerFree)
        timerIdentify = startTimer(fps);


    readyToFire = true;
}

void GameWidget::shoot()
{


    //create stone here
}

void GameWidget::createEnemy()
{
    const int leftLimit = 0;
    const int topLimit = -130;
    int newX = leftLimit + (rand() % 150);
    int newY = topLimit + (rand() % 250);
    enemy = new EnemyFace;
    scene->addItem(enemy);
    enemy->setPos(newX, newY);
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
        setPowerPlus(step);
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

bool GameWidget::inOwnArea(QPointF position)
{
    const int left = 0;
    const int top = -130;
    const int right = 220;
    const int bottom = 100;
    return (position.x() >= left && position.x() <= right) && (position.y() >= top && position.y() <= bottom);
}

void GameWidget::timerEvent(QTimerEvent *)
{
    // !!!
    QPointF newShift = enemy->getNextTranslation();
    QPointF newPos = enemy->pos() + newShift;
    if (!inOwnArea(newPos))
    {
        newPos -= 2 * newShift;
        enemy->runIntoWall();
    }

    //if (inOwnArea(newPos))  unnecessary
    enemy->setPos(newPos);

}

void GameWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF sceneRect = this->sceneRect();
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::darkGray);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GameWidget::setPowerPlus(int delta)
{
    if ((powerRate + delta < 5) || (powerRate + delta > 100))
        return;
    powerRate += delta;
    emit powerChanged(powerRate);
}

void GameWidget::setAnglePlus(int delta)
{
    if ((angleRate + delta < 5) || (angleRate + delta > 85))
        return;
    angleRate += delta;
    catapult->setCannonAngle(angleRate);
    emit angleChanged(angleRate);
}
