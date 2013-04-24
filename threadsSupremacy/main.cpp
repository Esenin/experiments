/*!
  @author Esenin
  Reserach project. Main purpose is to compare standart quicksort
  algorythm, in one thread and many
  */

#include <QtGui/QApplication>

#include "researchWidget.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    ResearchWidget window;
    window.show();

    return application.exec();
}
