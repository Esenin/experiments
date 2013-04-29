#include "researchWidget.h"
#include "ui_researchWidget.h"

ResearchWidget::ResearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResearchWidget),
    sorter(NULL)
{
    ui->setupUi(this);
    connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(startSortTest()));
    connect(&visualUpdater, SIGNAL(timeout()), this, SLOT(visualUpdaterEvent()));
    connect(ui->threadCounterSpin, SIGNAL(valueChanged(int)), SLOT(threadsCountChanged(int)));
}

ResearchWidget::~ResearchWidget()
{
    delete ui;
}

void ResearchWidget::sortFinished()
{
    visualUpdater.stop();
    ui->timeLcd->display(sortStartTime.msecsTo(QTime::currentTime()));

    qDebug() << "Sort results checking...";
    ui->sortVerifyCheckBox->setChecked(array->checkArray());

    qDebug() << "Done!";

    delete sorter;
    delete array;
    disconnect(this, SLOT(sortFinished()));
    ui->startBtn->setEnabled(true);
}

void ResearchWidget::startSortTest()
{
    ui->startBtn->setDisabled(true);
    qDebug() << "Sort init...";
    sortInit();
    visualUpdater.start(300);
    qDebug() << "Sort Start";
    startSort();
}

void ResearchWidget::visualUpdaterEvent()
{
    ui->timeLcd->display(sortStartTime.msecsTo(QTime::currentTime()));
}

void ResearchWidget::threadsCountChanged(const int &newLevel)
{
    ui->label->setText("Threads count: 2^(" + QString::number(newLevel + 1) + ") - 1");
}

void ResearchWidget::sortInit() throw(BadArraySize)
{
    int arrSize = ui->arrSizeEdit->text().toInt();
    if (!arrSize)
        throw BadArraySize();

    array = new ArrayMaster(arrSize);
    array->fillArrayRand();
    if (ui->simpleSortButton->isChecked())
        sorter = new QuickSorter(array->getArray(), arrSize);
    else
        sorter = new ThreadQSortMaster(array->getArray(), arrSize, ui->threadCounterSpin->value());

    QObject::connect(sorter, SIGNAL(sortFinished()), this, SLOT(sortFinished()));
}

void ResearchWidget::startSort()
{
    sortStartTime = QTime::currentTime();
    sorter->sort();
}
