#include "gameobject.h"
#include <QDebug>
GameObject::GameObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent) :
    xCoordinate(x), yCoordinate(y), size(size), QGraphicsItem(parent)
{
    setVisible(true);
}
QRectF GameObject::boundingRect() const{
    return QRectF(xCoordinate * size, yCoordinate * size, size, size);
    qDebug() << "boundingRect spucha";
}
void GameObject::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    qDebug() << "GameObject::paint spucha";
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(QRectF(xCoordinate * size, yCoordinate * size, size, size));
}
