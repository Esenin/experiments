#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGraphicsView>
#include <QtGui>
#include "gunMachine.h"
#include "enemyFace.h"

class GameWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GameWidget(QWidget *parent = 0);
    ~GameWidget();

signals:
    void powerChanged(int delta);
    void angleChanged(int delta);
    
    
protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void setPowerPlus(int delta);
    void setAnglePlus(int delta);
    bool inOwnArea(QPointF position);
    void createEnemy();
    void startRound();
    void shoot();

private:
    QGraphicsScene *scene;
    GunMachine *catapult;
    EnemyFace *enemy;
    int timerIdentify;
    int powerRate;
    int angleRate;
    bool readyToFire;
};

#endif // GAMEWIDGET_H
