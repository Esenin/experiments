#pragma once

#include <QtCore/QThread>

//! @class ThreadQSort makes quicksort with 2^deep threads
class ThreadQSort : public QThread
{
    Q_OBJECT
public:
    ThreadQSort(int *array, const int &begin, const int &end, const int level, const int maxDeep);
    ~ThreadQSort();

    void run();

protected:
    //! start quicksorts in separate thread in case level < maxDeep
    void tQSort(int *array, int first, int last);

    //! try to start recoursive sort branch in new thread
    bool startNewThreadSuccess(const int &left, const int &right);

private:
    int *mArray;
    const int mBegin;
    const int mEnd;
    const int mLevel;
    const int mMaxDeep;
    ThreadQSort *leftBranch;
    ThreadQSort *rightBranch;
};

