
#include "gamearea.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>

GameArea::GameArea(QWidget *parent) : QGraphicsView(parent)
{
    setStyleSheet("background-color: #0B4485;"
                  "    background-clip: padding;"
                  "color: #0B4485;"
                  "border-style: groove ;"
                  "border-radius: 5px;"
                  "border-width: 0px;"
                  "margin: 0px;"
                  "padding:10px;"
                  );
    qDebug() << this->width() << this->height();
    mainScene = new QGraphicsScene();
    //mainScene->setSceneRect(0, 0, this->width(), this->height());
    //mainScene->setBackgroundBrush(QBrush(QImage(":/images/vader.jpg").scaled(500, 5)));
    setScene(mainScene);
    Pacman = new QGraphicsPixmapItem();

    Pacman->setPixmap(QPixmap(":/images/Pac-man.gif"));
    //Pacman->setPos((mainScene->width() - Pacman->pixmap().width())/2, mainScene->height() - Pacman->pixmap().height() - 50);
    QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 1000, 500);
    //rect->setPos(300, 50);
    mainScene->addItem(Pacman);
    mainScene->addItem(rect);
    QGraphicsRectItem *rect2 = new QGraphicsRectItem(0, 500, 500, 500);
    mainScene->addItem(rect2);
}
