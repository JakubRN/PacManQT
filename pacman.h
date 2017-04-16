#ifndef PACMAN_H
#define PACMAN_H
#include "movingobject.h"
#include <set>
#include <QColor>
#include "ghost.h"
class Pacman : public MovingObject
{
    Q_OBJECT
    int pacmanStartAngle;
    int pacmanSpanAngle;
    const int pacmanRotationMinimunAngle;
    const int pacmanRotationMaximumAngle;
    bool pacmanOpens;
    int score;
    QColor pacmanColor;
    int superStateChangeFactor;
    QTimer colorChangeTimer;
    bool pacmanIsRed;
    int remainingTime;
    possibleDirections nextDirection;

    int ghostEatCount;
    QTimer resetTimer;
    QTimer redStateTimer;
    void manageSuperState();
public:
    bool pacmanIsResetting;
    Pacman(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    ~Pacman();
    QPainterPath shape() const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    void manageDirections() override;
    void stopMoving() override;
    void startMoving() override;
    int getScore();
    bool getRedState();
    void resetPacman(unsigned int x, unsigned int y);
    bool pacmanChangingColor();
    int getRemainingTime();
    void setNextDirection(possibleDirections dir);
signals:
    void positionChanged();
    void ghostEaten(Ghost *);
    void gameOver();
    void scoreChanged();
    void stopGhosts(int);
    void startGhosts();
public slots:
    void manageCollisions();
    void manageAngle();
    void angrierPacman();
    void normalPacman();
    void focusPacman();
};

#endif // PACMAN_H
