#include "gameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QGraphicsView(parent),
    catapultPosition(QPoint(-200, 100)),
    fps(42),
    powerRate(50),
    angleRate(45)
{
    initGraphicsOutput();

    connect(&gameTimer, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));
    connect(&visualTimer, SIGNAL(timeout()), this, SLOT(visualTimerEvent()));
    connect(&infinityClouds, SIGNAL(timeout()), this, SLOT(cloudsTimerEvent()));

    startGameSession();
}

GameWidget::~GameWidget()
{
    foreach (QGraphicsPixmapItem *item, cloudList)
    {
        scene->removeItem(item);
        delete item;
    }

    delete missile;
    delete enemy;
    delete catapult;
    delete infoMessage;
    delete gameOverMessage;
    delete scene;    
}

void GameWidget::initGraphicsOutput()
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

    gameOverMessage = new QGraphicsTextItem("Game Over! \nYou can restart game");
    gameOverMessage->setFont(QFont("Arial"));

    QString helpInfo = QString("Control:\n Left-right arrows to change gun power\n") +
            QString(" Up-down to change gun angle\n And spacebar to shoot\n 'God' Luck!");
    infoMessage = new QGraphicsTextItem(helpInfo);
    infoMessage->setFont(QFont("Arial", 10));
    scene->addItem(infoMessage);
    infoMessage->setPos(scene->sceneRect().topLeft());

    missile = new StoneMissile;
    enemy = new EnemyFace;

    createClouds();
}

void GameWidget::createClouds()
{
    const int cloudsCount = 5;
    QImage stdCloud("cloud.png");


    for (int i = 0; i < cloudsCount; i++)
    {
        cloudList << new QGraphicsPixmapItem(QPixmap::fromImage(stdCloud.scaled(QSize(100, 50))));
    }

    foreach (QGraphicsPixmapItem *item, cloudList)
    {
        scene->addItem(item);
        qreal xPos = (rand() % int(scene->width())) + scene->sceneRect().left();
        qreal yPos = (rand() % int(scene->height() / 3)) + scene->sceneRect().top();
        item->setPos(xPos, yPos);
    }
}

void GameWidget::startGameSession()
{
    shotsCount = 0;
    hitsCount = 0;
    currentTime = 40;
    if (scene->items().contains(missile))
        scene->removeItem(missile);

    if (scene->items().contains(gameOverMessage))
        scene->removeItem(gameOverMessage);

    startNewRound();

    gameTimer.start(999);
    infinityClouds.start(fps);
}

void GameWidget::startNewRound()
{
    createEnemy();

    recoveryTimeRemaining = 0;
    visualTimer.start(fps);

    readyToFire = true;
}

void GameWidget::shoot()
{
    if (!readyToFire || !gameTimer.isActive())
        return;
    const qreal horozontSpeedBooster = 1.1;

    scene->addItem(missile);
    missile->setPos(catapultPosition + catapult->getBulletExitPoint());

    energy = float(powerRate) / 100;
    missileSpeedVector =
            QPointF(catapult->getBulletExitPoint().x() * (energy * horozontSpeedBooster),
                    catapult->getBulletExitPoint().y() * energy);

    readyToFire = false;
    shotsCount++;
}

void GameWidget::createEnemy()
{
    if (scene->items().contains(enemy))
        return;

    const int leftLimit = 0;
    const int topLimit = -130;
    int newX = leftLimit + (rand() % 200);
    int newY = topLimit + (rand() % 200);
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
    const int top = int(scene->sceneRect().top());
    const int right = int(scene->sceneRect().right()) - 50;
    const int bottom = int(scene->sceneRect().bottom() -50);
    return (position.x() >= left && position.x() <= right) && (position.y() >= top && position.y() <= bottom);
}

void GameWidget::checkForKill()
{
    if (missile->collidesWithItem(enemy))
    {
        visualTimer.stop();
        scene->removeItem(missile);
        scene->removeItem(enemy);
        recoveryTimeRemaining = 1;
        hitsCount++;
    }
}

void GameWidget::setNextMissilePos()
{
    const qreal rotateAngle = 15;
    const qreal gravity = 2;
    if (!scene->items().contains(missile))
        return;

    missileSpeedVector.setY(missileSpeedVector.y() + gravity);
    missile->setPos(missile->pos() + missileSpeedVector);
    missile->rotate(rotateAngle);

    if (missile->pos().x() > scene->sceneRect().right() || missile->pos().y() > scene->sceneRect().bottom())
    {
        scene->removeItem(missile);
        readyToFire = true;
    }
    else
        checkForKill();
}

void GameWidget::setNextEmemyPos()
{
    if (!scene->items().contains(enemy))
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

void GameWidget::setNextCloudsPos()
{
    const qreal windSpeed = 2;
    foreach (QGraphicsPixmapItem *item, cloudList)
    {
        item->setPos(item->pos().x() + windSpeed, item->pos().y());
        if (item->pos().x() > scene->sceneRect().right() + item->boundingRect().width())
        {
            qreal yPos =(rand() % int(scene->height() / 3)) + scene->sceneRect().top();
            item->setPos(scene->sceneRect().left() - item->boundingRect().width(), yPos);
        }
    }
}


void GameWidget::visualTimerEvent()
{
    if (!scene->items().contains(enemy))
        return;

    setNextEmemyPos();
    setNextMissilePos();
}

void GameWidget::cloudsTimerEvent()
{
    setNextCloudsPos();
}

void GameWidget::gameTimerEvent()
{
    currentTime--;
    emit updateInfo(currentTime, hitsCount, shotsCount);

    if (currentTime <= 0)
        makeGameOver();

    if (--recoveryTimeRemaining == 0)
        startNewRound();
}

void GameWidget::makeGameOver()
{
    visualTimer.stop();
    gameTimer.stop();

    if (scene->items().contains(enemy))
        enemy->setPos(catapult->getBulletExitPoint());

    scene->addItem(gameOverMessage);
    gameOverMessage->setPos(scene->sceneRect().center());
}

void GameWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF sceneRect = this->sceneRect();
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::darkGray);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->drawRect(sceneRect);

    QPointF leftBeach = QPointF(scene->sceneRect().left(), catapultPosition.y());
    QRectF waterField = QRectF(leftBeach, sceneRect.bottomRight());
    QLinearGradient waterGradient(waterField.topLeft(), waterField.bottomRight());
    waterGradient.setColorAt(0, Qt::lightGray);
    waterGradient.setColorAt(1, Qt::darkBlue);
    painter->fillRect(rect.intersect(waterField), waterGradient);
    painter->drawRect(waterField);
}

void GameWidget::setPowerPlus(int delta)
{
    if ((powerRate + delta < 10) || (powerRate + delta > 100))
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
