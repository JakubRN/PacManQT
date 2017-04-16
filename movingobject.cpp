#include "movingobject.h"
#include <QThread>
#include <cmath>
#include <QDebug>
#include <level.h>
extern char boolBoard[26][26];
MovingObject::MovingObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) : GameObject(x, y, size, parent),
    timeDelay((double)200 / (size)), tempX(0), tempY(0), xDirection(0), yDirection(-1), currentDirection(possibleDirections::right), objectMoveTimer(),
    sizeShift(5), myBrush(Qt::white), movableDirections(0), coordinatesChanged(false)
{
    setTransformOriginPoint(size/2, size/2);
    objectMoveTimer.setSingleShot(false);
    QObject::connect(&objectMoveTimer, SIGNAL(timeout()), this, SLOT(move()));
    objectMoveTimer.start(timeDelay);
}

MovingObject::~MovingObject()
{
}

QRectF MovingObject::boundingRect() const
{
    return QRect(-sizeShift, -sizeShift, size +  2 * sizeShift, size + 2 * sizeShift);
}

void MovingObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    UNUSED_ARG(option);
    UNUSED_ARG(widget);
    painter->setBrush(myBrush);
    painter->drawRect(boundingRect());
}

void MovingObject::manageDirections()
{
    movableDirections.clear();
    if(xCoordinate != 25 && boolBoard[yCoordinate][xCoordinate + 1] != 0)
        movableDirections.push_back(possibleDirections::right);
    if(xCoordinate != 0 && boolBoard[yCoordinate][xCoordinate - 1] != 0)
        movableDirections.push_back(possibleDirections::left);
    if(yCoordinate != 25 && boolBoard[yCoordinate + 1][xCoordinate] != 0)
        movableDirections.push_back(possibleDirections::down);
    if(yCoordinate != 0 && boolBoard[yCoordinate - 1][xCoordinate] != 0)
        movableDirections.push_back(possibleDirections::up);
}

void MovingObject::stopMoving()
{
    objectMoveTimer.stop();
}

void MovingObject::startMoving()
{
        objectMoveTimer.start(timeDelay);
}

void MovingObject::move()
{
    if(coordinatesChanged) {
        coordinatesChanged = false;
        switch (currentDirection) {
        case possibleDirections::right:
            if(yCoordinate == 13 && xCoordinate == 25) {
                break;
            }
            if(xCoordinate == 25 || boolBoard[yCoordinate][xCoordinate + 1] == 0) {
                manageDirections();
                coordinatesChanged = true;
                return;
            }
            setRotation(0);
            xDirection = 1;
            yDirection = 0;
            break;
        case possibleDirections::left:
            if(yCoordinate == 13 && xCoordinate == 0) {
                break;
            }
            if(xCoordinate == 0 || boolBoard[yCoordinate][xCoordinate - 1] == 0) {
                manageDirections();
                coordinatesChanged = true;
                return;
            }
            setRotation(180);
            xDirection = -1;
            yDirection = 0;
            break;
        case possibleDirections::up:
            if(yCoordinate == 0 || boolBoard[yCoordinate - 1][xCoordinate] == 0) {
                manageDirections();
                coordinatesChanged = true;
                return;
            }
            setRotation(-90);
            yDirection = -1;
            xDirection = 0;
            break;
        case possibleDirections::down:
            if(yCoordinate == 25 || boolBoard[yCoordinate + 1][xCoordinate] == 0) {
                manageDirections();
                coordinatesChanged = true;
                return;
            }
            setRotation(90);
            yDirection = 1;
            xDirection = 0;
            break;
        }
    }
    tempX += xDirection;
    tempY += yDirection;
    setPos(x() + xDirection, y() + yDirection);
    if(abs((double)tempX) == size){
        if(yCoordinate == 13 && xCoordinate == 25) {
            xCoordinate = 0;
            setX(0);
        }
        else if(yCoordinate == 13 && xCoordinate == 0) {
            xCoordinate = 25;
            setX(25 * size + size);
        }
        else{
            tempX = 0;
            xCoordinate += xDirection;
        }
        coordinatesChanged = true;
        manageDirections();
    }
    else if(abs((double)tempY) == size) {
        tempY = 0;
        yCoordinate += yDirection;
        coordinatesChanged = true;
        manageDirections();
    }
}
