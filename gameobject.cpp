#include "gameobject.h"
#include <QDebug>
GameObject::GameObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) :
    xCoordinate(x), yCoordinate(y), size(size), QGraphicsItem(parent)
{
    setVisible(true);
    setPos(x * size, y * size);
}
QRectF GameObject::boundingRect() const{
    return QRectF(0, 0, size, size);
}
void GameObject::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(QRectF(0, 0, size, size));
}
