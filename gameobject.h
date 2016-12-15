#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QBrush>
#include <QPen>


class GameObject : public QGraphicsItem
{
protected:
    unsigned int xCoordinate;
    unsigned int yCoordinate;
    unsigned int size;
public:
    GameObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) = 0;
};

#endif // GAMEOBJECT_H
