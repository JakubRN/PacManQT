#include "gameobject.h"
#include <QDebug>
GameObject::GameObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) :
    xCoordinate(x), yCoordinate(y), size(size), QGraphicsItem(parent)
{
    setVisible(true);
//    setPos(x, y);
}
QRectF GameObject::boundingRect() const{
    return QRectF(xCoordinate * size, yCoordinate * size, size, size);
}
void GameObject::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(QRectF(xCoordinate * size, yCoordinate * size, size, size));
}
