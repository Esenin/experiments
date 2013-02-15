#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGraphicsView>
#include <QtGui>
#include "gunMachine.h"

class GameWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GameWidget(QWidget *parent = 0);

signals:
    void powerChanged(int delta);
    void angleChanged(int delta);
    
public slots:
    
protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void setPowerPlus(int delta);
    void setAnglePlus(int delta);
    void shoot();

private:
    GunMachine *catapult;
    int timerIdentify;
    int powerRate;
    int angleRate;
};

#endif // GAMEWIDGET_H
