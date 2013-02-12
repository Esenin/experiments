#include <QtGui/QApplication>
#include "catapult.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Catapult window;
    window.show();
    
    return application.exec();
}
