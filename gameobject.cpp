#include "gameobject.h"

GameObject::GameObject(unsigned int x, unsigned int y, unsigned int size, QAbstractGraphicsShapeItem *parent) :
    xCoordinate(x), yCoordinate(y), size(size), QAbstractGraphicsShapeItem(parent)
{

}
QRectF GameObject::boundingRect() const{
    return QRectF(xCoordinate * size, yCoordinate * size, size, size);
}
void GameObject::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->drawRect(xCoordinate * size, yCoordinate * size, size, size);
}
