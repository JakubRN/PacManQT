#ifndef PACMAN_H
#define PACMAN_H
#include "movingobject.h"
#include <set>
#include <QColor>
class Pacman : public MovingObject
{
    Q_OBJECT
    int pacmanStartAngle;
    int pacmanSpanAngle;
    const int pacmanRotationMinimunAngle;
    const int pacmanRotationMaximumAngle;
    bool pacmanOpens;
    std::set<int> keyPressed;
    void manageSuperState();
    QColor pacmanColor;
    int superStateChangeFactor;
    QTimer *colorChangeTimer;
    bool pacmanIsRed;
    int remainingTime;
    possibleDirections nextDirection;
    int score;
public:
    Pacman(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void managePressedKeys();
    void manageDirections() override;
    void stopMoving() override;
    void startMoving() override;
    int getScore();
signals:
    void scoreChanged();
    void stopGhosts(int);
    void startGhosts();
    void pauseGame();
public slots:
    void manageCollisions();
    void manageAngle();
    void angrierPacman();
    void normalPacman();
};

#endif // PACMAN_H
