#include "supercoin.h"
#define RADIUS ((double)size/2)

SuperCoin::SuperCoin(unsigned int x, unsigned int y, int size, GameObject *parent) : Coin(x, y, size, parent)
{

}

QRectF SuperCoin::boundingRect() const
{
    return QRectF(size * xCoordinate + size/2 - RADIUS/2, size * yCoordinate + size/2 - RADIUS/2,
                  RADIUS, RADIUS);
}

void SuperCoin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush((*new QBrush(Qt::yellow)));
    painter->drawEllipse(size * xCoordinate + size/2 - RADIUS/2, size * yCoordinate + size/2 - RADIUS/2,
                     RADIUS, RADIUS);

}
