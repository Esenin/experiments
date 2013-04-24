#include "arrayMaster.h"

ArrayMaster::ArrayMaster(const int dimension)
    : mSize(dimension),
      correctArray(NULL)
{
    array = new int[mSize];
}

ArrayMaster::~ArrayMaster()
{
    if (array)
        delete[] array;
    if (correctArray)
        delete[] correctArray;
}

int *ArrayMaster::getArray() const
{
    return array;
}

bool ArrayMaster::checkArray() throw(EmptyArray)
{
    if (!correctArray)
        throw EmptyArray();
    for (int i = 0; i < mSize; i++)
        if (array[i] != correctArray[i])
            return false;
    return true;
}

void ArrayMaster::fillArrayRand()
{
    const int randMax = 30042013;
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < mSize; i++)
        array[i] = rand() % randMax;

    prepareArrayForChecking();
}

const int ArrayMaster::size() const
{
    return mSize;
}

void ArrayMaster::prepareArrayForChecking()
{
    if (!correctArray)
        correctArray = new int[mSize];
    for (int i = 0; i < mSize; i++)
        correctArray[i] = array[i];
    QuickSorter validSorter(correctArray, mSize);
    validSorter.sort();
}
