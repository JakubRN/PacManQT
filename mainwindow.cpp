#include "mainwindow.h"
#include<QDebug>
#include <QStatusBar>
#define SIZE (1280, 960)


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet("background-color: #0A2038;"
                             "border-width: 0px;"
                             "padding: 0px;"
                             "margin: 0px;"
                  );

    //showFullScreen();
    resize(1280, 960);
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());
    //setFocusPolicy(Qt::StrongFocus);
    currentLevel = new Level(this->width(), this->height(), this);
    qDebug() << currentLevel->width() << currentLevel->height();
    currentLevel->setStyleSheet("QPushButton:pressed {"
                                 "color: yellow;"
                                 "background-color: blue;"
                                 "}"
                                  "QPushButton:focus{ background-color: green; }"
                                  "QPushButton:hover{ background-color: red; }"
                                  "QPushButton:checked { color: red; }");
    setCentralWidget(currentLevel);
    setWindowTitle(tr("PAC-MAN"));
    //resize(500,300);
    setWhatsThis(tr("My implementation of pac-man game"));
    setWindowIconText("LOL");
}

MainWindow::~MainWindow()
{

}
