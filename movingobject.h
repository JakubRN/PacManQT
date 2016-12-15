#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "gameobject.h"
#include <QTimer>
#include <QObject>
#include <vector>
#include <QBrush>

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
    QTimer *objectMoveTimer;
    int sizeShift;
    std::vector<possibleDirections> movableDirections;
    bool coordinatesChanged;
    QBrush myBrush;
public:
    MovingObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual void manageDirections() = 0;
    virtual void stopMoving();
    virtual void startMoving();
public slots:
    void move();
};

#endif // MOVINGOBJECT_H
