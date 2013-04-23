#pragma once

#include "sorter.h"
#include "threadQSort.h"

class ThreadQSortMaster : public Sorter
{
    Q_OBJECT
public:
    ThreadQSortMaster(int *array, const int &size, const int maxDeep);
    void sort();

signals:
    void sorted();
private slots:
    void threadFinished();
private:
    ThreadQSort *sorter;
    const QObject *listener;
};

