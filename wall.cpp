#include "wall.h"
#include <QBrush>
#include <QPen>
Wall::Wall(unsigned int x, unsigned int y, int size, GameObject *parent) : GameObject(x, y, size, parent)
{
    GameObject::setPen(QPen(QBrush(Qt::black), 2));
    GameObject::setBrush(*new QBrush(Qt::black));
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(xCoordinate * size + 1, yCoordinate * size + 1, size -1, size - 1);
}
