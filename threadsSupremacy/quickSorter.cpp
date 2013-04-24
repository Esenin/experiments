#include "quickSorter.h"

using std::swap;

QuickSorter::QuickSorter(int *array, int const size) :
    Sorter(array, size)
{
}

void QuickSorter::sort()
{
    int const arrStart = 0;
    qSort(insideArray, arrStart, arrSize - 1);
    emit sortFinished();
}

void QuickSorter::qSort(int *array, int first, int last)
{
    int left = first;
    int right = last;
    int pivot = array[(left + right) / 2];

    do
    {
        while (array[left] < pivot)
            left++;
        while (array[right] > pivot)
            right--;
        if (left <= right)
        {
            swap(array[left], array[right]);
            right--;
            left++;
        }
    }
    while (left <= right);

    if (left < last)
        qSort(array, left, last);
    if (right > first)
        qSort(array, first, right);
}
