#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QFrame>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include "gameobject.h"
#include "pacman.h"
#define BOARD_SIZE 26
class GameArea : public QGraphicsScene
{
    GameObject *boardArea[BOARD_SIZE][BOARD_SIZE];
    int SQUARE_SIZE;
protected:
public:
    Pacman *mainPacman;
    explicit GameArea(int w, int h, QWidget *parent = 0);

};

#endif // GAMEAREA_H
