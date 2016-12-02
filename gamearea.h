#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QFrame>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>

class GameArea : public QGraphicsScene
{
    QGraphicsPixmapItem *Pacman;
public:
    explicit GameArea(int w, int h, QWidget *parent = 0);

};

#endif // GAMEAREA_H
