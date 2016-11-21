#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "level.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
     Level * currentLevel;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H