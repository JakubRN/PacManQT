#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QAbstractGraphicsShapeItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class GameObject : public QAbstractGraphicsShapeItem
{

public:
    unsigned int xCoordinate;
    unsigned int yCoordinate;
    unsigned int size;
    GameObject(unsigned int x = 0, unsigned int y = 0, unsigned int size = 0, QAbstractGraphicsShapeItem *parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

#endif // GAMEOBJECT_H
