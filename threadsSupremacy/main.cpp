#include <QtGui/QApplication>
#include <QDebug>
#include <QTime>
#include <QWaitCondition>

#include "arrayMaster.h"
#include "quickSorter.h"
#include "ThreadQSortMaster.h"

int main(int argc, char *argv[])
{

    QApplication application(argc, argv);

    QTime commonTestTime(QTime::currentTime());

    const int size = 1000000;
//    ArrayMaster array(size);
//    array.fillArrayRand();

//    QuickSorter qSorter(array.getArray(), array.size());

//    QTime startTime(QTime::currentTime());



//    qDebug() << "sort started";

//    qSorter.sort();

//    qDebug() << startTime.msecsTo(QTime::currentTime());

//    qDebug() << array.checkArray();

//    qDebug() << "Total time per test in seconds:";
//    qDebug() << commonTestTime.secsTo(QTime::currentTime());

    ///////////////////////////////////////////

    ArrayMaster array2(size);
    array2.fillArrayRand();

    ThreadQSortMaster threadSorter(array2.getArray(), array2.size());

    QTime startTime(QTime::currentTime());

    //threadSorter.print();   //

    qDebug() << "sort started";

    threadSorter.sort();



    //threadSorter.print();   //

    qDebug() << "sort time in ms:";
    qDebug() << startTime.msecsTo(QTime::currentTime());

    qDebug() << array2.checkArray();

    qDebug() << "Total time per test in seconds:";
    qDebug() << commonTestTime.secsTo(QTime::currentTime());




    return 0;
}
