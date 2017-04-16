#include "wall.h"
extern char boolBoard[26][26];
Wall::Wall(unsigned int x, unsigned int y, int size, GameObject *parent) : GameObject(x, y, size, parent)
{

}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    UNUSED_ARG(option);
    UNUSED_ARG(widget);
    painter->setPen(QPen(QBrush(Qt::black), 0));
    painter->setBrush(*new QBrush(Qt::black));
    int tempX, tempY, tempDestX, tempDestY;
    if(xCoordinate > 0) {
        if(boolBoard[yCoordinate][xCoordinate - 1] == 0)
            tempX = 0;
        else tempX = (double)size/4;
    }
    else tempX = 0;
    if(xCoordinate < 25) {
        if(boolBoard[yCoordinate][xCoordinate + 1] == 0)
            tempDestX = size - 1;
        else tempDestX =size * (double)3/4;
    }
    else tempDestX = size - 1;

    if(yCoordinate > 0) {
        if(boolBoard[yCoordinate - 1][xCoordinate] == 0)
            tempY = 0;
        else tempY = (double)size/4;
    }
    else tempY = 0;
    if(yCoordinate < 25) {
        if(boolBoard[yCoordinate + 1][xCoordinate] == 0)
            tempDestY = size - 1;
        else tempDestY =  size * (double)3/4;
    }
    else tempDestY = size - 1;


    painter->drawRect(tempX, tempY, tempDestX - tempX, tempDestY - tempY);

}
