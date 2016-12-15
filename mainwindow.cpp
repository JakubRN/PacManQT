#include "mainwindow.h"
#include<QDebug>
#include <QStatusBar>
#define SIZE (1280, 960)
#include <QApplication>
#include <QDesktopWidget>
#include <memory>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet("background-color: #0A2038;"
                             "border-width: 0px;"
                             "padding: 0px;"
                             "margin: 0px;"
                  );

    //showFullScreen();
    resize(1280, 900);
    //QRect screen = QApplication::desktop()->screenGeometry();
    //resize(screen.width()/2, screen.height()/2);
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    std::unique_ptr<Level> currentLevel(new Level(this->width(), this->height(), this));

    currentLevel.get()->setStyleSheet("QPushButton:pressed {"
                                 "color: yellow;"
                                 "background-color: blue;"
                                 "}"
                                  "QPushButton:focus{ background-color: green; }"
                                  "QPushButton:hover{ background-color: red; }"
                                  "QPushButton:checked { color: red; }");
    setCentralWidget(currentLevel.get());
    setWindowTitle(tr("PAC-MAN"));
    setWhatsThis(tr("My implementation of pac-man game"));
    setWindowIconText("-");
    currentLevel.release();
}

MainWindow::~MainWindow()
{

}
