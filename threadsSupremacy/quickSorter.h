#pragma once

#include "sorter.h"

//!  Quick sort realisation class
/*!
  inherited from interface
  Doesnt need own destructor
*/
class QuickSorter : public Sorter
{
public:
    QuickSorter(int *array, int const size);
    //! essential override func
    void sort();
protected:
    //! main function of this class
    /*!
        quick sort realisation
    */
    void qSort(int *array, int first, int last);
};


