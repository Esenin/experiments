#pragma once

#include <QtGui/QWidget>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

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
    void visualUpdaterEvent();
    void threadsCountChanged(const int &newLevel);

protected:
    class BadArraySize {};

    void sortInit() throw(BadArraySize);
    void startSort();

private:
    Ui::ResearchWidget *ui;
    Sorter *sorter;
    QTime sortStartTime;
    ArrayMaster *array;
    QTimer visualUpdater;
};

