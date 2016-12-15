#ifndef LEVEL_H
#define LEVEL_H

#include <Qt>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QSizePolicy>
#include <QStyle>
#include <QDebug>
#include <vector>
#include <QPalette>
#include <memory>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "gameobject.h"
#include "pacman.h"
#include "ghost.h"
#include "wall.h"
#include "coin.h"
#include "supercoin.h"
#include "movingobject.h"
#define BOARD_SIZE 26
class Level : public QWidget
{
    Q_OBJECT
    unsigned int pacmanLifes;
    std::unique_ptr<QPushButton> pause;
    std::unique_ptr<QPushButton> start;
    std::unique_ptr<QPushButton> mainMenu;
    std::unique_ptr <QLCDNumber> scoreLcd;
    std::unique_ptr <QGridLayout> layout;
    std::unique_ptr <QGraphicsScene> board;
    std::unique_ptr <QGraphicsView> view;
    std::unique_ptr <QHBoxLayout> lifeBoxes;
    GameObject *boardArea[BOARD_SIZE][BOARD_SIZE];
    int SQUARE_SIZE;
    int Score;
    bool stopOrNot;
    std::unique_ptr<Pacman>mainPacman;
    Ghost blueGhost;
    Ghost redGhost;
    Ghost orangeGhost;
    Ghost pinkGhost;
    QLabel *getLabel(QString &input);
    void createLayout();
    void createBoard();
    void addMovingItems();
public:
    explicit Level(int w, int h, QWidget *parent = 0);
    QPushButton *initButton(const char *myString);
    bool gameStopped();
    void stopGhosts();
signals:
    void coinWasEaten();
public slots:
    void waitForIt(int);
    void increaseScore();
    void pauseGame();
    void startGame();
    void managePausedGame();
    void returnToMainMenu();
    void startGhosts();

};

#endif // LEVEL_H
