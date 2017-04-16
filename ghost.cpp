#include "ghost.h"
#include <string>
#include <cstdlib>
//#include <cmath>
#include <vector>
#include <QDebug>
#define ASSUMED_RED_PACMAN_TIME 2500
Ghost::Ghost(unsigned int x, unsigned int y, unsigned int size, const char *color, QGraphicsItem *parent) :
    MovingObject(x, y, size, parent), ghostColor(myColors::red), previousDirection(currentDirection),
    eventTimer(), tempTimeInterval(0), mainPacman(-1, -1, false), chasePacman(false), oneMoreStep(0)
{
    sizeShift = -1;
    currentDirection = possibleDirections::up;
    setRotation(-90);
    if(strcmp(color, "red") == 0){
        myBrush = QBrush(QColor("#CC0000"));
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
        myBrush = QBrush(QColor("#CC00CC"));
    ghostColor = myColors::pink;
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    UNUSED_ARG(option);
    UNUSED_ARG(widget);
    painter->setBrush(myBrush);
    painter->drawRoundedRect(boundingRect(), 10, 10);
    painter->setBrush(Qt::black);
    painter->drawEllipse(QPoint(size * 4/6, size / 2), size/4, size/4);
    if(chasePacman) {
        if(mainPacman.isRedState)
            painter->setBrush(Qt::white);
        else
            painter->setBrush(Qt::red);
    }
    else {
        painter->setBrush(QBrush(QColor("#808080")));
    }
    painter->drawEllipse(QPoint(size * 4/6, size / 2), size/6, size/6);
}

QPainterPath Ghost::shape() const
{
    QPainterPath path;
    path.addRoundedRect(boundingRect(), 10, 10);
    return path;
}


void Ghost::casualWalking()
{
    possibleDirections reversedDir = getReversedDirection();
    int temp;
    do {
        temp = rand()%movableDirections.size();
    }
    while(reversedDir == movableDirections[temp]);
    currentDirection = movableDirections[temp];
}

void Ghost::manageDirections()
{
    MovingObject::manageDirections();
    if(oneMoreStep != 0) {
        casualWalking();
        oneMoreStep--;
        return;
    }
    if(!chasePacman)
        casualWalking();
    else {
        if(xCoordinate == mainPacman.xCoordinate && yCoordinate == mainPacman.yCoordinate) {
            chasePacman = false;
            emit pacmanLost();
            casualWalking();
        }
        else {
            std::set<possibleDirections> preferredDirections(movableDirections.begin(), movableDirections.end());
            if(mainPacman.isRedState) {
                preferredDirections.clear();
                runAway(preferredDirections);
                //possibleDirections reversedDir = getReversedDirection();
                for(int i = 0; i < movableDirections.size(); i++)
                    if (preferredDirections.find(movableDirections[i]) != preferredDirections.end()) {
                        currentDirection = movableDirections[i];
                        return;
                }
            }
            else {
                if(abs((double)(mainPacman.xCoordinate - xCoordinate)) < abs((double)(mainPacman.yCoordinate - yCoordinate))) {
                    if ((int)(mainPacman.yCoordinate - yCoordinate) > 0){
                        if(preferredDirections.find(possibleDirections::down) != preferredDirections.end()) {
                            currentDirection = possibleDirections::down;
                            return;
                        }
                    }
                    else {
                        if(preferredDirections.find(possibleDirections::up) != preferredDirections.end()) {
                            currentDirection =possibleDirections::up;
                            return;
                        }
                    }
                }
                else if(abs((double)mainPacman.xCoordinate - xCoordinate) > abs((double)mainPacman.yCoordinate - yCoordinate)){
                    if ((int)(mainPacman.xCoordinate - xCoordinate) > 0){
                        if(preferredDirections.find(possibleDirections::right) != preferredDirections.end()) {
                            currentDirection = possibleDirections::right;
                            return;
                        }
                    }
                    else {
                        if(preferredDirections.find(possibleDirections::left) != preferredDirections.end()) {
                            currentDirection = possibleDirections::left;
                            return;
                        }
                    }
                }
                else {
                    preferredDirections.clear();
                    follow(preferredDirections);
                }
            }
            casualWalking();
            oneMoreStep = 2;
            //chasePacman = false;
//            for(int i = 0; i < movableDirections.size(); i++) {
//                if(preferredDirections.find(movableDirections[i]) != preferredDirections.end()){

//                    currentDirection = movableDirections[i];
//                    return;
//                }
//            }
//            qDebug() << "jajebie";
//            casualWalking();
        }
    }
}

void Ghost::pacmanNoticed(int x, int y, bool isRed)
{
    mainPacman.xCoordinate = x;
    mainPacman.yCoordinate = y;
    mainPacman.isRedState  = isRed;
    chasePacman = true;
    eventTimer.setSingleShot(true);
    connect(&eventTimer, SIGNAL(timeout()), this, SLOT(pacmanNotRed()));
    eventTimer.start(ASSUMED_RED_PACMAN_TIME);
}

possibleDirections Ghost::getReversedDirection()
{
    switch (currentDirection) {
    case possibleDirections::right:
        return possibleDirections::left;
    case possibleDirections::left:
        return possibleDirections::right;
    case possibleDirections::up:
        return possibleDirections::down;
    case possibleDirections::down:
        return possibleDirections::up;
    }
    return possibleDirections::right;
}

void Ghost::runAway(std::set<possibleDirections> &preferredDirections)
{
    if(mainPacman.xCoordinate > xCoordinate)
        preferredDirections.insert(possibleDirections::left);
    else if (mainPacman.xCoordinate < xCoordinate)
        preferredDirections.insert(possibleDirections::right);
    else {
        preferredDirections.insert(possibleDirections::left);
        preferredDirections.insert(possibleDirections::right);
    }
    if (mainPacman.yCoordinate > yCoordinate)
        preferredDirections.insert(possibleDirections::up);
    else if (mainPacman.yCoordinate < yCoordinate)
        preferredDirections.insert(possibleDirections::down);
    else {
        preferredDirections.insert(possibleDirections::up);
        preferredDirections.insert(possibleDirections::down);
    }
}

void Ghost::follow(std::set<possibleDirections> &preferredDirections)
{
    if(mainPacman.xCoordinate > xCoordinate)
        preferredDirections.insert(possibleDirections::right);
    else if (mainPacman.xCoordinate < xCoordinate)
        preferredDirections.insert(possibleDirections::left);
    else {
        preferredDirections.insert(possibleDirections::left);
        preferredDirections.insert(possibleDirections::right);
    }
    if (mainPacman.yCoordinate > yCoordinate)
        preferredDirections.insert(possibleDirections::up);
    else if (mainPacman.yCoordinate < yCoordinate)
        preferredDirections.insert(possibleDirections::down);
    else {
        preferredDirections.insert(possibleDirections::up);
        preferredDirections.insert(possibleDirections::down);
    }
}

void Ghost::resetGhost(unsigned int x, unsigned int y)
{
    chasePacman = false;
    xCoordinate = x;
    yCoordinate = y;
    tempX = 0;
    xDirection = 0;
    yDirection = -1;
    tempY = 0;
    currentDirection = possibleDirections::up;
    setRotation(-90);
    setPos(xCoordinate * size, yCoordinate * size);
    stopMoving();
    eventTimer.setSingleShot(true);
    connect(&eventTimer, SIGNAL(timeout()), this, SLOT(startMoving()));
    eventTimer.start(RESET_TIME_INTERVAL);
    //update();
}

void Ghost::stopMoving()
{
    MovingObject::stopMoving();
    if(eventTimer.isActive()){
        tempTimeInterval = eventTimer.remainingTime();
        eventTimer.stop();
    }
}

void Ghost::startMoving()
{
    MovingObject::startMoving();
    if(tempTimeInterval != 0) {
        eventTimer.start(tempTimeInterval);
        tempTimeInterval = 0;
    }
}

void Ghost::pacmanHidden()
{
    if(chasePacman)
        chasePacman = false;
}

void Ghost::pacmanNotRed()
{
    if( mainPacman.isRedState )
    mainPacman.isRedState = false;
}
