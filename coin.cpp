#include "coin.h"
#define RADIUS ((double)size/4)
Coin::Coin(unsigned int x, unsigned int y, int size, GameObject *parent) : GameObject(x, y, size, parent), radius(RADIUS)
{}

QRectF Coin::boundingRect() const
{
    return QRectF( size/2 - radius/2, size/2 - radius/2,
                  radius, radius);
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(*new QBrush(QColor("#ffd800")));
    painter->drawEllipse( size/2 - radius/2, size/2 - radius/2,
                         radius, radius);
}
