#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gameWidget = new GameWidget;

    ui->mainLayout->addWidget(gameWidget);
    connect(gameWidget, SIGNAL(powerChanged(int)), ui->lcdNumber, SLOT(display(int)));
    connect(gameWidget, SIGNAL(angleChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(gameWidget, SIGNAL(updateInfo(int,int,int)),
            this, SLOT(updateDisplayInfo(int,int,int)));

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->pushButtonRestart, SIGNAL(clicked()),
            gameWidget, SLOT(startGameSession()));
    connect(ui->pushButtonRestart, SIGNAL(clicked()),
            gameWidget, SLOT(setFocus()));

}


MainWindow::~MainWindow()
{
    delete gameWidget;
    delete ui;    
}

void MainWindow::updateDisplayInfo(int timer, int hits, int shotsCount)
{
    ui->lcdNumberTimer->display(timer);
    ui->lcdNumberHitsCount->display(hits);
    ui->lcdNumberShotsCount->display(shotsCount);
}


