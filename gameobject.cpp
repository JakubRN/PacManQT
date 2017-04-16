#include "gameobject.h"
#include <QDebug>
GameObject::GameObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) :
    xCoordinate(x), yCoordinate(y), size(size), QGraphicsItem(parent)
{
    setPos(x * size, y * size);
}

QRectF GameObject::boundingRect() const{
    return QRectF(0, 0, size, size);
}

int GameObject::getX()
{
    return xCoordinate;
}

int GameObject::getY()
{
    return yCoordinate;
}
void GameObject::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget *widget) {
    UNUSED_ARG(option);
    UNUSED_ARG(widget);
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(QRectF(boundingRect()));
}
