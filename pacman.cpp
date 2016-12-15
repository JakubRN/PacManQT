#include "pacman.h"
#include <QPixmap>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include "coin.h"
#include "supercoin.h"
#include <QColor>
#include <QGraphicsScene>
#define PACMAN_IMAGE_WIDTH 200
#define ANGLE_MULTIPLICATION_UNIT 16
#define OPEN_MOUTH_PACE 3
#define REPETITION_TIMES 20
void Pacman::manageSuperState()
{
    objectMoveTimer->stop();
    emit stopGhosts(REPETITION_TIMES * 80);
    colorChangeTimer->setInterval(80);
    colorChangeTimer->setSingleShot(false);
    connect(colorChangeTimer, SIGNAL(timeout()), this, SLOT(angrierPacman()));
    colorChangeTimer->start();
}

Pacman::Pacman(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) : MovingObject(x, y, size, parent),
    pacmanStartAngle(30), pacmanSpanAngle(300),
    pacmanRotationMinimunAngle(5), pacmanRotationMaximumAngle(55), pacmanOpens(true), score(0), pacmanColor("#ffd800"),
    superStateChangeFactor(0), colorChangeTimer(new QTimer()), pacmanIsRed(false), remainingTime(0), nextDirection(right)
{
    coordinatesChanged = true;
    setFlag(QGraphicsItem::ItemIsFocusable);
    QObject::connect(objectMoveTimer, SIGNAL(timeout()), this, SLOT(manageAngle()));
    QObject::connect(objectMoveTimer, SIGNAL(timeout()), this, SLOT(manageCollisions()));
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(*new QBrush(pacmanColor));
    painter->drawPie(boundingRect(), ANGLE_MULTIPLICATION_UNIT * pacmanStartAngle, ANGLE_MULTIPLICATION_UNIT * pacmanSpanAngle);
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    keyPressed.insert(event->key());
    managePressedKeys();
}

void Pacman::keyReleaseEvent(QKeyEvent *event)
{
    keyPressed.erase(event->key());
}

void Pacman::managePressedKeys()
{
    for(auto i : keyPressed){
        switch(i) {
        case Qt::Key_Left:
            nextDirection = left;
            break;
        case Qt::Key_Right:
            nextDirection = right;
            break;
        case Qt::Key_Up:
            nextDirection = up;
            break;
        case Qt::Key_Down:
            nextDirection = down;
            break;
        case Qt::Key_Space:
            emit pauseGame();
        }
    }
}

void Pacman::manageDirections()
{
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
    if(pacmanIsRed) {
        remainingTime = colorChangeTimer->remainingTime();
    }
    colorChangeTimer->stop();
    objectMoveTimer->stop();
}

void Pacman::startMoving()
{
    if(pacmanIsRed)
        colorChangeTimer->start(remainingTime);
    else if(superStateChangeFactor != 0)
        colorChangeTimer->start();
    if(superStateChangeFactor == 0)
        objectMoveTimer->start();
}

int Pacman::getScore()
{
    return score;
}


void Pacman::manageCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems(Qt::IntersectsItemShape);
    for(auto &i : collisions) {
        if(typeid(*i) == typeid(Coin)) {
            scene()->removeItem(i);
            delete i;
            score += 1;
            emit(scoreChanged());
        }
        else if(typeid(*i) == typeid(SuperCoin)) {
            scene()->removeItem(i);
            delete i;
            score += 5;
            emit(scoreChanged());
            if(!pacmanIsRed)
                manageSuperState();
            else {
                colorChangeTimer->start();
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
        colorChangeTimer->stop();
        disconnect(colorChangeTimer, SIGNAL(timeout()), this, SLOT(angrierPacman()));
        timeDelay = (double)timeDelay/1.5;
        objectMoveTimer->start(timeDelay);
        emit startGhosts();
        colorChangeTimer->setInterval(8000);
        colorChangeTimer->setSingleShot(true);
        connect(colorChangeTimer, SIGNAL(timeout()), this, SLOT(normalPacman()));
        colorChangeTimer->start();
        superStateChangeFactor = 0;
    }
}

void Pacman::normalPacman()
{
    timeDelay = 1.5 * timeDelay;
    objectMoveTimer->start(timeDelay);
    pacmanColor = QColor("#ffd800");
    colorChangeTimer->stop();
    disconnect(colorChangeTimer, SIGNAL(timeout()), this, SLOT(normalPacman()));
    pacmanIsRed = false;
}
