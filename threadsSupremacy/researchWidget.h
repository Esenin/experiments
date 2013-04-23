#pragma once

#include <QtGui/QWidget>
#include <QtCore/QTime>

#include "arrayMaster.h"
#include "quickSorter.h"
#include "ThreadQSortMaster.h"

namespace Ui {
class ResearchWidget;
}

class ResearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResearchWidget(QWidget *parent = 0);
    ~ResearchWidget();

protected slots:
    void sortFinished();
    void startSortTest();

protected:
    void sortInit();
    void startSort();

private:
    Ui::ResearchWidget *ui;
    Sorter *sorter;
    QTime startTime;
    ArrayMaster *array;
};

