#ifndef COIN_H
#define COIN_H

#include "gameobject.h"

class Coin : public GameObject
{
protected:
    int radius;
public:
    Coin(unsigned int x, unsigned int y, int size, GameObject *parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QPainterPath shape() const override;
};

#endif // COIN_H
