#ifndef GHOST_H
#define GHOST_H

#include "movingobject.h"
#include <set>
class Ghost : public MovingObject
{
    Q_OBJECT
    enum myColors {
        red = 0,
        blue = 1,
        orange = 2,
        pink = 3
    };
    struct PacmanProperties {
        unsigned int xCoordinate;
        unsigned int yCoordinate;
        bool isRedState;
        PacmanProperties(int x, int y, bool state) : xCoordinate(x), yCoordinate(y), isRedState(state) {}
    };
    myColors ghostColor;
    possibleDirections previousDirection;
    QTimer eventTimer;
    int tempTimeInterval;
    PacmanProperties mainPacman;
    bool chasePacman;
    int oneMoreStep;
    possibleDirections getReversedDirection();
    void runAway(std::set<possibleDirections> &);
    void follow(std::set<possibleDirections> &);
public:
   Ghost(unsigned int x, unsigned int y, unsigned int size, const char *, QGraphicsItem *parent = 0);
   void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
   QPainterPath shape() const override;
   void casualWalking();
   void manageDirections() override;
   void pacmanNoticed(int x, int y, bool isRed);
   void resetGhost(unsigned int x, unsigned int y);
   void stopMoving() override;
   void startMoving() override;
   void pacmanHidden();
signals:
   void pacmanLost();
public slots:
   void pacmanNotRed();
};

#endif // GHOST_H
