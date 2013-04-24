#pragma once

#include <QtCore/QObject>
#include <QtCore/QDebug>

//! Sorter class interface
/*!  Class includes all you need
    to inherit different sorters
*/
class Sorter : public QObject
{
    Q_OBJECT
public:
    //! Base construcor for regular sorter class
    /*!
    @param array your sort subject
    @param size int size of array
    */
    Sorter(int *array, int const size);

    //! Destructor must be virtual
    virtual ~Sorter() {}

    //! Pure virtual function you may override in your class
    virtual void sort() = 0;
    void print() const;

signals:
    void sortFinished();

protected:
    int *insideArray;
    const int arrSize;
};

