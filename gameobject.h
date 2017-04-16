#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QBrush>
#include <QPen>

#define UNUSED_ARG(arg) ((void)(arg))

class GameObject : public QGraphicsItem
{
protected:
    unsigned int size;
    unsigned int xCoordinate;
    unsigned int yCoordinate;
public:
    GameObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) = 0;
    int getX();
    int getY();
};

#endif // GAMEOBJECT_H
