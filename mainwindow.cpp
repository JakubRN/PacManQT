#include "mainwindow.h"
#include<QDebug>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet("background-color: #0A2038;"
                             "border-width: 0px;"
                             "padding: 0px;"
                             "margin: 0px;"
                  );
    showFullScreen();
    //qDebug() << width() << height();
    //setFocusPolicy(Qt::StrongFocus);
    currentLevel = new Level();
    setCentralWidget(currentLevel);
    setWindowTitle(tr("PAC-MAN"));
    //resize(500,300);
    setWhatsThis(tr("My implementation of pac-man game"));
    setWindowIconText("LOL");

}

MainWindow::~MainWindow()
{

}
