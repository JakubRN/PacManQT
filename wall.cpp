#include "wall.h"
#include <QBrush>
#include <QPen>
#include "gamearea.h"
extern char board[26][26];
Wall::Wall(unsigned int x, unsigned int y, int size, GameObject *parent) : GameObject(x, y, size, parent)
{

}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setBrush(*new QBrush(Qt::black));
    int tempX, tempY, tempDestX, tempDestY;
    if(xCoordinate > 0) {
        if(board[yCoordinate][xCoordinate - 1] == 0)
            tempX = xCoordinate* size;
        else tempX = xCoordinate * size + (double)size/4;
    }
    else tempX = xCoordinate* size;
    if(xCoordinate < 25) {
        if(board[yCoordinate][xCoordinate + 1] == 0)
            tempDestX = (xCoordinate + 1)* size - 1;
        else tempDestX = xCoordinate * size  + size * (double)3/4;
    }
    else tempDestX = (xCoordinate + 1)* size - 1;

    if(yCoordinate > 0) {
        if(board[yCoordinate - 1][xCoordinate] == 0)
            tempY = yCoordinate* size;
        else tempY = yCoordinate * size + (double)size/4;
    }
    else tempY = yCoordinate* size;
    if(yCoordinate < 25) {
        if(board[yCoordinate + 1][xCoordinate] == 0)
            tempDestY = (yCoordinate + 1)* size - 1;
        else tempDestY = yCoordinate * size  + size * (double)3/4;
    }
    else tempDestY = (yCoordinate + 1)* size - 1;


    painter->drawRect(tempX, tempY, tempDestX - tempX, tempDestY - tempY);

}
