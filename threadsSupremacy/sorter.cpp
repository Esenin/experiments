#include "sorter.h"

using std::swap;

Sorter::Sorter(int *array, int const size)
    : arrSize(size)
{
    insideArray = array;
}

void Sorter::print() const
{
    for (int i = 0; i < arrSize; i++)
    {
        qDebug() << insideArray[i];
    }
}
