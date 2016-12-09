#include "wall.h"

#include "gamearea.h"
extern char board[26][26];
Wall::Wall(unsigned int x, unsigned int y, int size, GameObject *parent) : GameObject(x, y, size, parent)
{

}

QRectF Wall::boundingRect() const
{
    return QRectF(0, 0, size, size);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QBrush(Qt::gray), 1));
    painter->setBrush(*new QBrush(Qt::black));
    int tempX, tempY, tempDestX, tempDestY;
    if(xCoordinate > 0) {
        if(board[yCoordinate][xCoordinate - 1] == 0)
            tempX = 0;
        else tempX = (double)size/4;
    }
    else tempX = 0;
    if(xCoordinate < 25) {
        if(board[yCoordinate][xCoordinate + 1] == 0)
            tempDestX = size - 1;
        else tempDestX =size * (double)3/4;
    }
    else tempDestX = size - 1;

    if(yCoordinate > 0) {
        if(board[yCoordinate - 1][xCoordinate] == 0)
            tempY = 0;
        else tempY = (double)size/4;
    }
    else tempY = 0;
    if(yCoordinate < 25) {
        if(board[yCoordinate + 1][xCoordinate] == 0)
            tempDestY = size - 1;
        else tempDestY =  size * (double)3/4;
    }
    else tempDestY = size - 1;


    painter->drawRect(tempX, tempY, tempDestX - tempX, tempDestY - tempY);

}
