#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "gameWidget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateDisplayInfo(int timer, int hits, int shotsCount);

private:
    Ui::MainWindow *ui;
    GameWidget *gameWidget;
};

#endif // MAINWINDOW_H
