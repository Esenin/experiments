#include "researchWidget.h"
#include "ui_researchWidget.h"

ResearchWidget::ResearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResearchWidget),
    sorter(NULL)
{
    ui->setupUi(this);
    connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(startSortTest()));
}

ResearchWidget::~ResearchWidget()
{
    delete ui;
}

void ResearchWidget::sortFinished()
{
    ui->timeLcd->display(startTime.msecsTo(QTime::currentTime()));
    ui->sortVerifyCheckBox->setChecked(array->checkArray());

    delete sorter;
    delete array;
    disconnect(this, SLOT(sortFinished()));
}

void ResearchWidget::startSortTest()
{
    sortInit();
    startSort();
}

void ResearchWidget::sortInit()
{
    int arrSize = ui->arrSizeEdit->text().toInt();
    if (!arrSize)
        return;

    array = new ArrayMaster(arrSize);
    array->fillArrayRand();
    if (ui->simpleSortButton->isChecked())
        sorter = new QuickSorter(array->getArray(), arrSize);
    else
        sorter = new ThreadQSortMaster(array->getArray(), arrSize, ui->threadCounterSpin->value());

    connect();
}

ResearchWidget::startSort()
{
    startTime = QTime::currentTime();
    sorter->sort();
}
