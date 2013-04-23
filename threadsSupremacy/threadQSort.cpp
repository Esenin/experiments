#include "threadQSort.h"

using std::swap;

ThreadQSort::ThreadQSort(int *array, const int &begin, const int &end, const int level, const int maxDeep)
    : QThread(),
      mArray(array),
      mBegin(begin),
      mEnd(end),
      mLevel(level),
      mMaxDeep(maxDeep),
      leftBranch(NULL)
{
}

ThreadQSort::~ThreadQSort()
{
    if (!leftBranch)
        delete leftBranch;
}

void ThreadQSort::run()
{
    tQSort(mArray, mBegin, mEnd);
}

void ThreadQSort::tQSort(int *array, int first, int last)
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
        if (!startNewThreadSuccess(left, last))
            tQSort(array, left, last);
    if (right > first)
        if (!startNewThreadSuccess(first, right))
            tQSort(array, first, right);
}

bool ThreadQSort::startNewThreadSuccess(const int &left, const int &right)
{
    if (mLevel >= mMaxDeep)
        return false;

    ThreadQSort *newBranch = new ThreadQSort(mArray, left, right, mLevel + 1, mMaxDeep);

    if (!leftBranch)
    {
        leftBranch = newBranch;
        leftBranch->start(HighPriority);
    }
    else
    {
        newBranch->start(HighPriority);
        while (!newBranch->wait());
        delete newBranch;
    }
    return true;
}
