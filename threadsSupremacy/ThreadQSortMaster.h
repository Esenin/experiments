#pragma once

#include "sorter.h"
#include "threadQSort.h"

//! @class ThreadQSortMaster package of thread quick sort in Sorter object
class ThreadQSortMaster : public Sorter
{
    Q_OBJECT
public:
    ThreadQSortMaster(int *array, const int &size, const int maxDeep);
    ~ThreadQSortMaster();
    void sort();

private slots:
    void threadFinished();
private:
    ThreadQSort *sorter;
};

