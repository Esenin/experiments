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


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
