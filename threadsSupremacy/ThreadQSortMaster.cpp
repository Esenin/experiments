#include "ThreadQSortMaster.h"

ThreadQSortMaster::ThreadQSortMaster(int *array, const int &size, const int maxDeep)
    : Sorter(array, size)
{
    sorter = new ThreadQSort(array, 0, size - 1, 0, maxDeep);
    QObject::connect(sorter, SIGNAL(finished()), this, SLOT(threadFinished()));
}

ThreadQSortMaster::~ThreadQSortMaster()
{
    delete sorter;
}

void ThreadQSortMaster::sort()
{
    sorter->start(QThread::NormalPriority);
}

void ThreadQSortMaster::threadFinished()
{
    emit sortFinished();
}
