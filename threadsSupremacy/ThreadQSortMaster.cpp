#include "ThreadQSortMaster.h"

ThreadQSortMaster::ThreadQSortMaster(int *array, const int &size, const int maxDeep)
    : Sorter(array, size),
      listener(receiver)
{
    sorter = new ThreadQSort(array, 0, size - 1, 0, maxDeep);
}

void ThreadQSortMaster::sort()
{
    sorter->start(QThread::HighPriority);
}

void ThreadQSortMaster::threadFinished()
{
    emit sorted();
}
