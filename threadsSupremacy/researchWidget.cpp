#include "researchWidget.h"
#include "ui_researchWidget.h"

ResearchWidget::ResearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResearchWidget)
{
    ui->setupUi(this);
}

ResearchWidget::~ResearchWidget()
{
    delete ui;
}
