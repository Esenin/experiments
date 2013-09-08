/*!
  Experiment with mem leaks

  Results: no memory leaks on android
  (got leaks on windows e.g.)
  */

#include <QtWidgets\QApplication>

#include "MainWindow.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow window;
	window.show();

	return app.exec();
}
