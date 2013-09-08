#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startLeak()));
	connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopLeak()));
	connect(&leakTimer, SIGNAL(timeout()), this, SLOT(leakTimerEvent()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::startLeak()
{
	leakTimer.start(ui->lineEdit->text().toInt());
}

void MainWindow::stopLeak()
{
	leakTimer.stop();
}

void MainWindow::leakTimerEvent()
{
	int arrSize = ui->spinBox->text().toInt();
	int *leakArr = new int[arrSize];

	qDebug() << "new arr: " << (sizeof(int) * arrSize) << " bytes";
	Q_UNUSED(leakArr);
}
