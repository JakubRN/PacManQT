#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "gameobject.h"
#include <QTimer>
#include <QObject>
#include <vector>
#include <QBrush>
#include <QPainterPath>
#define RESET_TIME_INTERVAL 1500
enum class possibleDirections {
    left,
    right,
    up,
    down
};
class MovingObject :  public QObject, public GameObject
{
    Q_OBJECT
protected:
    int tempX, tempY;
    int xDirection, yDirection;

    double timeDelay;
    possibleDirections currentDirection;
    QTimer objectMoveTimer;
    int sizeShift;
    std::vector<possibleDirections> movableDirections;
    bool coordinatesChanged;
    QBrush myBrush;
public:
    MovingObject(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    ~MovingObject();
    QRectF boundingRect() const;
    virtual QPainterPath shape() const = 0;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual void manageDirections() = 0;
    virtual void stopMoving();
public slots:
    virtual void startMoving();
    void move();
};

#endif // MOVINGOBJECT_H
