#include "pacman.h"
#include "coin.h"
#include "supercoin.h"
#include <QPixmap>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QColor>
#include <QGraphicsScene>
#define PACMAN_IMAGE_WIDTH 200
#define ANGLE_MULTIPLICATION_UNIT 16
#define OPEN_MOUTH_PACE 3
#define REPETITION_TIMES 20
#define RED_STATE_LENGTH 4500
#define YELLOW_PACMAN "#ffd800"
#define COLOR_CHANGE_PACE 70
#define START_ANGLE 30
#define SPAN_ANGLE 300
void Pacman::manageSuperState()
{
    MovingObject::stopMoving();
    emit stopGhosts((REPETITION_TIMES + 2)* COLOR_CHANGE_PACE);
    colorChangeTimer.start(COLOR_CHANGE_PACE);
}

Pacman::Pacman(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) : MovingObject(x, y, size, parent),
    pacmanStartAngle(30), pacmanSpanAngle(300),
    pacmanRotationMinimunAngle(5), pacmanRotationMaximumAngle(55), pacmanOpens(true), score(0), pacmanColor(YELLOW_PACMAN),
    superStateChangeFactor(0), colorChangeTimer(), pacmanIsRed(false), remainingTime(0), nextDirection(possibleDirections::right), ghostEatCount(1),
    resetTimer(), redStateTimer(), pacmanIsResetting(false)
{
//    setFlag(QGraphicsItem::ItemIsFocusable);
    coordinatesChanged = true;
//    currentDirection = right;
//    setRotation(0);
//    xDirection = 1;
//    yDirection = 0;
    resetTimer.setSingleShot(true);
    connect(&resetTimer, SIGNAL(timeout()), this, SLOT(startMoving()));
    connect(&resetTimer, SIGNAL(timeout()), this, SLOT(focusPacman()));

    colorChangeTimer.setSingleShot(false);
    connect(&colorChangeTimer, SIGNAL(timeout()), this, SLOT(angrierPacman()));

    redStateTimer.setSingleShot(true);
    connect(&redStateTimer, SIGNAL(timeout()), this, SLOT(normalPacman()));

    QObject::connect(&objectMoveTimer, SIGNAL(timeout()), this, SLOT(manageAngle()));
    QObject::connect(&objectMoveTimer, SIGNAL(timeout()), this, SLOT(manageCollisions()));
}

Pacman::~Pacman()
{
}

QPainterPath Pacman::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    UNUSED_ARG(option);
    UNUSED_ARG(widget);
    painter->setBrush(*new QBrush(pacmanColor));
    painter->drawPie(boundingRect(), ANGLE_MULTIPLICATION_UNIT * pacmanStartAngle, ANGLE_MULTIPLICATION_UNIT * pacmanSpanAngle);
}


void Pacman::manageDirections()
{
    emit positionChanged();
    MovingObject::manageDirections();
    for(auto &i : movableDirections) {
        if( i == nextDirection) {
            currentDirection = nextDirection;
            return;
        }
    }
}

void Pacman::stopMoving()
{

    if(pacmanChangingColor())
        colorChangeTimer.stop();
    else
        MovingObject::stopMoving();
        if(pacmanIsRed) {
            remainingTime = redStateTimer.remainingTime();
            redStateTimer.stop();
        }
}

void Pacman::startMoving()
{
    if(pacmanChangingColor())
        colorChangeTimer.start();
    else {
        MovingObject::startMoving();
        if(pacmanIsRed) redStateTimer.start(remainingTime);
    }

}

int Pacman::getScore()
{
    return score;
}

bool Pacman::getRedState()
{
    return pacmanIsRed;
}

void Pacman::resetPacman(unsigned int x, unsigned int y)
{
    xCoordinate = x;
    yCoordinate = y;
    tempX = 0;
    tempY = 0;
    currentDirection = possibleDirections::right;
    xDirection = 1;
    yDirection = 0;
    setRotation(0);
    pacmanStartAngle = START_ANGLE;
    pacmanSpanAngle = SPAN_ANGLE;
    setPos(xCoordinate * size, yCoordinate * size);
    pacmanIsResetting = true;
    stopMoving();
    resetTimer.start(RESET_TIME_INTERVAL);
}

bool Pacman::pacmanChangingColor()
{
    if(superStateChangeFactor == 0)
        return false;
    else return true;
}

int Pacman::getRemainingTime()
{
    return (REPETITION_TIMES - superStateChangeFactor) * 100;
}

void Pacman::setNextDirection(possibleDirections dir)
{
    nextDirection = dir;
}


void Pacman::manageCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems(Qt::IntersectsItemShape);

    for(auto &i : collisions) {
//        = qgraphicsitem_cast<GameObject *>(i);
        if(typeid(*i) == typeid(Coin)) {
            scene()->removeItem(i);
            //delete i;
            score += 5;
            emit(scoreChanged());
        }
        else if(typeid(*i) == typeid(SuperCoin)) {
            scene()->removeItem(i);
            //delete i;
            score += 25;
            emit(scoreChanged());
            if(!pacmanIsRed)
                manageSuperState();
            else {
                redStateTimer.start();
            }
        }
        else if(typeid(*i) == typeid(Ghost)) {
            if(!pacmanIsRed) {
                emit(gameOver());
            }
            else {
                emit(ghostEaten((static_cast<Ghost *>(i))));
                score += ghostEatCount * 100;
                ghostEatCount++;
                emit(scoreChanged());
            }
        }
    }
}

void Pacman::manageAngle()
{
    if(pacmanOpens) {
        if(pacmanStartAngle <= pacmanRotationMaximumAngle) {
            pacmanStartAngle += OPEN_MOUTH_PACE;
            pacmanSpanAngle -= OPEN_MOUTH_PACE * 2;
        }
        else {
            pacmanOpens = false;
            return;
        }
    }
    else {
        if(pacmanStartAngle >= pacmanRotationMinimunAngle) {
            pacmanStartAngle -= OPEN_MOUTH_PACE;
            pacmanSpanAngle += OPEN_MOUTH_PACE * 2;
        }
        else {
            pacmanOpens = true;
            return;
        }
    }
    update();
}

void Pacman::angrierPacman()
{
    superStateChangeFactor++;
    pacmanColor.setRgb(255, pacmanColor.green() - 10, pacmanColor.blue());
    update();
    if(superStateChangeFactor == REPETITION_TIMES) {
        pacmanIsRed = true;
        colorChangeTimer.stop();
        emit startGhosts();
        superStateChangeFactor = 0;
        timeDelay = (double)timeDelay/1.5;
        redStateTimer.start(RED_STATE_LENGTH);
        MovingObject::startMoving();
    }
}

void Pacman::normalPacman()
{
    ghostEatCount = 1;
    pacmanColor = QColor(YELLOW_PACMAN);
    pacmanIsRed = false;
    timeDelay = 1.5 * timeDelay;
    MovingObject::startMoving(); //just resetting the clock with different time delay
}

void Pacman::focusPacman()
{
    pacmanIsResetting = false;
}
