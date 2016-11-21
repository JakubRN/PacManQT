#include "mainwindow.h"
#include<QDebug>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    showFullScreen();
    //qDebug() << width() << height();
    //setFocusPolicy(Qt::StrongFocus);
    currentLevel = new Level();
    setCentralWidget(currentLevel);
    setWindowTitle(tr("PAC-MAN"));
    //resize(500,300);
    setWhatsThis(tr("My implementation of pac-man game"));
    setWindowIconText("LOL");
    setStyleSheet("color: blue; background-color: ffffff;"
                  );
}

MainWindow::~MainWindow()
{

}
