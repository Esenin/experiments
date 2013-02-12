#include "catapult.h"
#include "ui_catapult.h"

Catapult::Catapult(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Catapult)
{
    ui->setupUi(this);

    mainScene = new QGraphicsScene();
    ui->viewer->setScene(mainScene);

    drawTextHints();

    mainScene->addRect(QRectF(0, 0, 100, 100));
    QGraphicsItem *item = mainScene->itemAt(50, 50);
    QTransform matrix = item->transform();
    matrix.rotate(45);
    item->setTransform(matrix);


    mainScene->setFocusItem(item);


    ui->viewer->scale(0.7, 0.7);
}

Catapult::~Catapult()
{
    delete ui;
}

void Catapult::drawTextHints()
{
    QFont backFont("Arial", 12, 1, true);

    QGraphicsTextItem *angleInfo =
            mainScene->addText("Press up-down to setup gun's angle", backFont);

    QTransform matrix = angleInfo->transform();
    matrix.translate(150, 150);
    angleInfo->setTransform(matrix);

    QGraphicsTextItem *powerInfo =
            mainScene->addText("Press left-right to setup gun's power", backFont);

    matrix = powerInfo->transform();
    matrix.translate(150, 200);
    powerInfo->setTransform(matrix);

    QGraphicsTextItem *shotInfo =
            mainScene->addText("Press Space to make a shot", backFont);

    matrix = shotInfo->transform();
    matrix.translate(150, 250);
    shotInfo->setTransform(matrix);

}

void Catapult::on_actionExit_triggered()
{
    ui->powerDisplay->display(50);
}
