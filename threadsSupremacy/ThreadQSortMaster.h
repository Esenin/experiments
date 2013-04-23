#pragma once

#include "sorter.h"
#include "threadQSort.h"

class ThreadQSortMaster : public Sorter
{
public:
    ThreadQSortMaster(int *array, int const &size, int const maxDeep = 3);
    void sort();

    bool wait();
private:
    ThreadQSort *sorter;
};

