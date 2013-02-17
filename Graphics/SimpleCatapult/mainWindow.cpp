#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    keyWidget = new GameWidget;

    ui->mainLayout->addWidget(keyWidget);
    connect(keyWidget, SIGNAL(powerChanged(int)), ui->lcdNumber, SLOT(display(int)));
    connect(keyWidget, SIGNAL(angleChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(keyWidget, SIGNAL(updateInfo(int,int,int)),
            this, SLOT(updateDisplayInfo(int,int,int)));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->pushButtonRestart, SIGNAL(clicked()),
            keyWidget, SLOT(startGameSession()));
    connect(ui->pushButtonRestart, SIGNAL(clicked()),
            keyWidget, SLOT(setFocus()));

}


MainWindow::~MainWindow()
{
    delete keyWidget;
    delete ui;    
}

void MainWindow::updateDisplayInfo(int timer, int hits, int shotsCount)
{
    ui->lcdNumberTimer->display(timer);
    ui->lcdNumberHitsCount->display(hits);
    ui->lcdNumberShotsCount->display(shotsCount);
}

