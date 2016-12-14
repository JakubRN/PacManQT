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
public:
    int score;
    Pacman(unsigned int x, unsigned int y, unsigned int size, QGraphicsItem *parent = 0);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void managePressedKeys();
signals:
    void scoreChanged();
    void stopGhosts();
    void startGhosts();
public slots:
    void manageCollisions();
    void manageAngle();
    void angrierPacman();
    void normalPacman();
};

#endif // PACMAN_H
