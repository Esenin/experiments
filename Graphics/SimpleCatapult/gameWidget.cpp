#include "gameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QGraphicsView(parent),
    enemy(NULL),
    missile(NULL),
    catapultPosition(QPoint(-200, 100)),
    fps(42),
    powerRate(50),
    angleRate(45)
{
    initGraphicOutput();

    connect(&gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));
    connect(&visualTimerDEBUG, SIGNAL(timeout()), this, SLOT(visualTimerEvent()));

    startGameSession();
}

GameWidget::~GameWidget()
{
    delete catapult;
    delete scene;
}

void GameWidget::initGraphicOutput()
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
    catapult->setPos(catapultPosition);
}

void GameWidget::startGameSession()
{
    shotsCount = 0;
    hitsCount = 0;
    currentTime = 30;

    startNewRound();

    gameTimer.start(999);
}

void GameWidget::startNewRound()
{
    createEnemy();

    recoveryTimeRemaining = 0;
    visualTimerDEBUG.start(fps);

    readyToFire = true;
    recoveryTimeRemaining = 0;
}

void GameWidget::shoot()
{
    if (!readyToFire)
        return;

    missile = new StoneMissile;
    scene->addItem(missile);
    missile->setPos(catapultPosition + catapult->getBulletExitPoint());

    readyToFire = false;
    energy = float(powerRate) / 100;
    shotsCount++;
}

void GameWidget::createEnemy()
{
    if (enemy != NULL)
        return;

    const int leftLimit = 0;
    const int topLimit = -130;
    int newX = leftLimit + (rand() % 150);
    int newY = topLimit + (rand() % 250);
    enemy = new EnemyFace;
    scene->addItem(enemy);
    enemy->setPos(newX, newY);
}

void GameWidget::destroyItem(QGraphicsItem *element)
{
    if (element == NULL)
        return;

    delete element;
    element = NULL;
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

void GameWidget::setNextMissilePos()
{
    const qreal rotateAngle = 15;
    const qreal gravity = -10;
    if (missile == NULL)
        return;

    QPointF shift = QPointF(catapult->getBulletExitPoint().x() * energy,
                            catapult->getBulletExitPoint().y() * energy);
    missile->setPos(missile->pos() + shift);
    missile->rotate(rotateAngle);

    if (missile->pos().x() > scene->sceneRect().right() || missile->pos().y() > scene->sceneRect().bottom())
    {
        destroyItem(missile);
        readyToFire = true;
        return;
    }

    checkForKill();

}


void GameWidget::checkForKill()
{
    if (missile->collidesWithItem(enemy))
    {
        visualTimerDEBUG.stop();
        destroyItem(missile);
        destroyItem(enemy);
        recoveryTimeRemaining = 2;
        hitsCount++;
    }
}

void GameWidget::setNextEmemyPos()
{
    if (enemy == NULL)
        return;

    QPointF newShift = enemy->getNextTranslation();
    QPointF newPos = enemy->pos() + newShift;
    if (!inOwnArea(newPos))
    {
        newPos -= 2 * newShift;
        enemy->runIntoWall();
    }

    enemy->setPos(newPos);
}

void GameWidget::visualTimerEvent()
{
    if (enemy == NULL)
        return;

    setNextEmemyPos();
    setNextMissilePos();

}

void GameWidget::gameTimerEvent()
{
    currentTime--;
    emit updateInfo(currentTime, hitsCount, shotsCount);

    if (currentTime < 0)
    {
        visualTimerDEBUG.stop();
        destroyItem(enemy);
        gameTimer.stop();
    }

    if (--recoveryTimeRemaining == 0)
    {
        startNewRound();
    }

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
