#pragma once

#include <QtWidgets\QMainWindow>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void startLeak();
	void stopLeak();
	void leakTimerEvent();

private:
	Ui::MainWindow *ui;
	QTimer leakTimer;
};

