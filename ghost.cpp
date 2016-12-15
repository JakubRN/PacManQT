#include "ghost.h"
#include <string>
#include <cstdlib>

Ghost::Ghost(unsigned int x, unsigned int y, unsigned int size, const char *color, QGraphicsItem *parent) :
    MovingObject(x, y, size, parent), ghostColor(myColors::red), previousDirection(currentDirection)
{
    sizeShift = -2;
    currentDirection = up;
    setPos(this->x(), this->y());
    if(strcmp(color, "red") == 0){
        myBrush = Qt::red;
        ghostColor = myColors::red;
    }
    if(strcmp(color, "blue") == 0) {
        myBrush = QBrush(QColor("#2177DA"));
        ghostColor = myColors::blue;
    }
   if(strcmp(color, "orange") == 0)
    {
       myBrush = Qt::yellow;
       ghostColor = myColors::orange;
    }
    if(strcmp(color, "pink") == 0)
        myBrush = Qt::magenta;
        ghostColor = myColors::pink;
}

void Ghost::casualWalking()
{

}

void Ghost::manageDirections()
{
    MovingObject::manageDirections();
    possibleDirections reversedDir = getReversedDirection();
    int temp;
    do {
        temp = rand()%static_cast<possibleDirections>(movableDirections.size());
    }
    while(reversedDir == movableDirections[temp]);
    currentDirection = movableDirections[temp];
}

MovingObject::possibleDirections Ghost::getReversedDirection()
{
    switch (currentDirection) {
    case right:
        return left;
    case left:
        return right;
    case up:
        return down;
    case down:
        return up;
    }
    return right;
}
