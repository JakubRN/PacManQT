#ifndef WALL_H
#define WALL_H
#include "gameobject.h"

class Wall : public GameObject
{
public:
    Wall(unsigned int x, unsigned int y, int size, GameObject *parent = 0);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

#endif // WALL_H
