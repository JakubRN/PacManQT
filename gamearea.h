#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QFrame>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>

class GameArea : public QGraphicsView
{
    QGraphicsScene * mainScene;
    QGraphicsPixmapItem *Pacman;
public:
    explicit GameArea(QWidget *parent = 0);
};

#endif // GAMEAREA_H
