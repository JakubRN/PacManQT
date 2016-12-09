#ifndef SUPERCOIN_H
#define SUPERCOIN_H

#include "coin.h"

class SuperCoin : public Coin
{
public:
    SuperCoin(unsigned int x, unsigned int y, int size, GameObject *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

};

#endif // SUPERCOIN_H
