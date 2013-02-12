#ifndef CATAPULT_H
#define CATAPULT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>


namespace Ui {
class Catapult;
}

class Catapult : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Catapult(QWidget *parent = 0);
    ~Catapult();
    
private slots:

    void on_actionExit_triggered();

private:
    Ui::Catapult *ui;
    QGraphicsScene *mainScene;

    void drawTextHints();
};

#endif // CATAPULT_H
