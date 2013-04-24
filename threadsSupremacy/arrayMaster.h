#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QTime>
#include "quickSorter.h"


//! @class ArrayMaster array host with specific methods
class ArrayMaster
{
public:
    class EmptyArray {};

    explicit ArrayMaster(const int dimension);
    ~ArrayMaster();

    int* getArray() const;

    //! checks array for incremantion and numbers safety by comparing with valid model
    bool checkArray() throw (EmptyArray);

    //! also saves array state
    void fillArrayRand();

    const int size() const;

protected:

    //! saves count of every num for post-checking
    void prepareArrayForChecking();


private:
    int *array;
    const int mSize;
    int *correctArray;
};

