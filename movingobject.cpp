#include "movingobject.h"
#include <QThread>
#include <cmath>
#include <gamearea.h>
extern char board[26][26];
MovingObject::MovingObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) : GameObject(x, y, size, parent),
    timeDelay((double)300 / (size)), currentDirection(right), tempX(0), tempY(0), timer(new QTimer),
    xDirection(0), yDirection(0)
{
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
    timer->setSingleShot(false);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(timeDelay);
}

QRectF MovingObject::boundingRect() const
{
    return QRect(xCoordinate*size + tempX, yCoordinate*size + tempY, size, size);
}

void MovingObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(*new QBrush(Qt::white));
    painter->drawRect(xCoordinate*size + tempX, yCoordinate*size + tempY, size, size);
}

void MovingObject::move()
{
    switch (currentDirection) {
    case right:
        if(xCoordinate == 25 || board[yCoordinate][xCoordinate + 1] == 0)
            return;
        xDirection = 1;
        break;
    case left:
        if(xCoordinate == 0 || board[yCoordinate][xCoordinate - 1] == 0)
            return;
        xDirection = -1;
        break;
    case up:
        if(yCoordinate == 0 || board[yCoordinate - 1][xCoordinate] == 0)
            return;
        yDirection = -1;
        break;
    case down:
        if(yCoordinate == 25 || board[yCoordinate + 1][xCoordinate] == 0)
            return;
        yDirection = 1;
        break;
    }
    tempX += xDirection;
    tempY += yDirection;
    if(tempX == size){
        tempX = 0;
        xCoordinate += 1;
    }
    else if(abs((double)tempY) == size) {
        tempY = 0;
        yCoordinate += yDirection;
    }
    //update();
}
