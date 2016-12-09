#include "coin.h"
#define RADIUS ((double)size/4)
Coin::Coin(unsigned int x, unsigned int y, int size, GameObject *parent) : GameObject(x, y, size, parent)
{

}

QRectF Coin::boundingRect() const
{
    return QRectF(size * xCoordinate + size/2 - RADIUS/2, size * yCoordinate + size/2 - RADIUS/2,
                  RADIUS, RADIUS);
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush((*new QBrush(Qt::yellow)));
    painter->drawEllipse(size * xCoordinate + size/2 - RADIUS/2, size * yCoordinate + size/2 - RADIUS/2,
                         RADIUS, RADIUS);
}
