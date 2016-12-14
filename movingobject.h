#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "gameobject.h"
#include <QTimer>
#include <QObject>
class MovingObject :  public QObject, public GameObject
{
    Q_OBJECT
    int tempX, tempY;
    int xDirection, yDirection;
protected:
    enum possibleDirections {
        left = 0,
        right = 1,
        up = 2,
        down = 3
    };
    double timeDelay;
    possibleDirections currentDirection;
    possibleDirections nextDirection;
    QTimer *objectMoveTimer;
    int sizeShift;
public:
    MovingObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void manageDirections();
public slots:
    void move();
};

#endif // MOVINGOBJECT_H
