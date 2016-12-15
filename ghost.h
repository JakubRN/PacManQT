#ifndef GHOST_H
#define GHOST_H

#include "movingobject.h"

class Ghost : public MovingObject
{
    enum myColors {
        red = 0,
        blue = 1,
        orange = 2,
        pink = 3
    };
    myColors ghostColor;
    possibleDirections previousDirection;
public:
   Ghost(unsigned int x, unsigned int y, unsigned int size, const char *, QGraphicsItem *parent = 0);
   void casualWalking();
   void manageDirections() override;
   possibleDirections getReversedDirection();
public slots:
};

#endif // GHOST_H
