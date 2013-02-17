#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGraphicsView>
#include <QtGui>
#include <QTimer>
#include "gunMachine.h"
#include "enemyFace.h"
#include "stoneMissile.h"


class GameWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GameWidget(QWidget *parent = 0);
    ~GameWidget();

public slots:
    void startGameSession();


signals:
    void powerChanged(int delta);
    void angleChanged(int delta);
    void updateInfo(int timer, int hits, int shotsCount);

    
protected:
    void keyPressEvent(QKeyEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void startNewRound();
    void destroyItem(QGraphicsItem *element);
    void initGraphicOutput();
    void checkForKill();
    void setNextMissilePos();
    void setNextEmemyPos();
    void setPowerPlus(int delta);
    void setAnglePlus(int delta);
    bool inOwnArea(QPointF position);
    void createEnemy();
    void shoot();

private:
    QGraphicsScene *scene;
    QTimer gameTimer;
    QTimer visualTimerDEBUG;
    GunMachine *catapult;
    EnemyFace *enemy;
    StoneMissile *missile;
    qreal energy;
    QPoint catapultPosition;
    const int fps;
    int recoveryTimeRemaining;
    int powerRate;
    int angleRate;
    int currentTime;
    int shotsCount;
    int hitsCount;
    bool readyToFire;


private slots:
    void gameTimerEvent();
    void visualTimerEvent();

};

#endif // GAMEWIDGET_H
