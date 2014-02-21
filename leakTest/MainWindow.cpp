#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, mLeaked(0)
{
	ui->setupUi(this);
	connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startLeak()));
	connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopLeak()));
	connect(&mLeakTimer, SIGNAL(timeout()), this, SLOT(leakTimerEvent()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::startLeak()
{
	mLeakTimer.start(ui->lineEdit->text().toInt());
}

void MainWindow::stopLeak()
{
	mLeakTimer.stop();
}

void MainWindow::leakTimerEvent()
{
	int arrSize = ui->spinBox->text().toInt();
	int *leakArr = new int[arrSize];


	qDebug() << "new arr: " << (sizeof(int) * arrSize) << " bytes";
	double ticLeak = double(sizeof(int) * arrSize) / (1024 * 1024); // byte -> kilo -> Mb
	mLeaked += ticLeak;

	ui->ticLeakLabel->setText("Leaks per tic:	" + QString::number(ticLeak) + "Mb");
	ui->leakLabel->setText("Leaked:		" + QString::number(mLeaked) + "Mb  +/- 1%");

	Q_UNUSED(leakArr);
}
