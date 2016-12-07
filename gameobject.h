#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class GameObject : public QGraphicsItem
{

public:
    unsigned int xCoordinate;
    unsigned int yCoordinate;
    unsigned int size;
    GameObject(unsigned int x = 0, unsigned int y = 0, unsigned int size = 0, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

#endif // GAMEOBJECT_H
