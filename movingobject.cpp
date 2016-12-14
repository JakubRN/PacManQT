#include "movingobject.h"
#include <QThread>
#include <cmath>
#include <gamearea.h>
#include <QDebug>
#include <set>
#include "coin.h"
extern char board[26][26];
MovingObject::MovingObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) : GameObject(x, y, size, parent),
    timeDelay((double)500 / (size)), tempX(0), tempY(0), xDirection(0), yDirection(0), currentDirection(right), objectMoveTimer(new QTimer()),
    sizeShift(5), nextDirection(down)
{
    setTransformOriginPoint(size/2, size/2);
    objectMoveTimer->setSingleShot(false);
    QObject::connect(objectMoveTimer, SIGNAL(timeout()), this, SLOT(move()));
    objectMoveTimer->start(timeDelay);
}

QRectF MovingObject::boundingRect() const
{
    return QRect(-sizeShift, -sizeShift, size +  2 * sizeShift, size + 2 * sizeShift);
}

void MovingObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(*new QBrush(Qt::white));
    painter->drawRect(boundingRect());
}

void MovingObject::manageDirections()
{
    std::set<int> movableDirections;
    if(xCoordinate != 25 && board[yCoordinate][xCoordinate + 1] != 0)
        movableDirections.insert(possibleDirections::right);
    if(xCoordinate != 0 && board[yCoordinate][xCoordinate - 1] != 0)
        movableDirections.insert(possibleDirections::left);
    if(yCoordinate != 25 && board[yCoordinate + 1][xCoordinate] != 0)
        movableDirections.insert(possibleDirections::down);
    if(yCoordinate != 0 && board[yCoordinate - 1][xCoordinate] != 0)
        movableDirections.insert(possibleDirections::up);
    if( movableDirections.find(nextDirection) != movableDirections.end())
        currentDirection = nextDirection;


}

void MovingObject::move()
{
    switch (currentDirection) {
    case right:
        if(xCoordinate == 25 || board[yCoordinate][xCoordinate + 1] == 0) {
            currentDirection = nextDirection;
            return;
        }
        setRotation(0);
        xDirection = 1;
        yDirection = 0;
        break;
    case left:
        if(xCoordinate == 0 || board[yCoordinate][xCoordinate - 1] == 0) {
            currentDirection = nextDirection;
            return;      
        }
        setRotation(180);
        xDirection = -1;
        yDirection = 0;
        break;
    case up:
        if(yCoordinate == 0 || board[yCoordinate - 1][xCoordinate] == 0) {
            currentDirection = nextDirection;
            return;
        }
        setRotation(-90);
        yDirection = -1;
        xDirection = 0;
        break;
    case down:
        if(yCoordinate == 25 || board[yCoordinate + 1][xCoordinate] == 0) {
            currentDirection = nextDirection;
            return;
        }
        setRotation(90);
        yDirection = 1;
        xDirection = 0;
        break;
    }
    tempX += xDirection;
    tempY += yDirection;
    setPos(x() + xDirection, y() + yDirection);
    if(abs((double)tempX) == size){
        tempX = 0;
        xCoordinate += xDirection;
        manageDirections();
    }
    else if(abs((double)tempY) == size) {
        tempY = 0;
        yCoordinate += yDirection;
        manageDirections();
    }
}
