#include "arrayMaster.h"


ArrayMaster::ArrayMaster(const int dimension)
    : mSize(dimension)
{
    array = new int[mSize];
}

ArrayMaster::~ArrayMaster()
{
    if (array)
        delete array;
}

int *ArrayMaster::getArray() const
{
    return array;
}

bool ArrayMaster::checkArray()
{
    RBTree<int> current;
    try
    {
        saveState(current, true);
        qDebug() << "state saved";
    }
    catch(SortFailed const &)
    {
        return false;
    }

    if (current.size() != revision.size())
        return false;

    for (RBTree<int>::ConstIterator iterator(revision); !iterator.end(); iterator++)
    {
        if (current.exists(iterator.current().first) != iterator.current().second)
            return false;
    }

    return true;
}

void ArrayMaster::fillArrayRand()
{
    const int randMax = 30042013;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < mSize; i++)
        array[i] = qrand() % randMax;

    saveState(revision);
}

const int ArrayMaster::size() const
{
    return mSize;
}

void ArrayMaster::saveState(RBTree<int> &box, const bool checkSort) throw(SortFailed)
{
    for (int i = 0; i < mSize; i++)
    {
        box.add(array[i]);

        if (checkSort && i > 0)
        {
            if (array[i] < array[i - 1])
                throw SortFailed();
        }
    }

}
