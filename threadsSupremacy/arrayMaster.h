#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QTime>
#include <QDebug>

#include "rBTree.h"


//! @class ArrayMaster array host with specific operations group
class ArrayMaster
{
public:
    explicit ArrayMaster(const int dimension);
    ~ArrayMaster();

    int* getArray() const;

    //! checks array for incremantion and numbers safety
    bool checkArray();

    //! also saves array state
    void fillArrayRand();

    const int size() const;

protected:
    class SortFailed{};

    //! saves count of every num for post-checking
    void saveState(RBTree<int> &box, const bool checkSort = false) throw(SortFailed);


private:
    int *array;
    const int mSize;
    RBTree<int> revision;
};

