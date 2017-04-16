#ifndef LEVEL_H
#define LEVEL_H

#include<QKeyEvent>
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
    std::unique_ptr<Ghost> blueGhost;
    std::unique_ptr<Ghost> redGhost;
    std::unique_ptr<Ghost> orangeGhost;
    std::unique_ptr<Ghost> pinkGhost;
    QTimer ghostTimer;
    bool gameOver;
    QTimer resetTimer;
    std::vector<QWidget *> pacmans;
    QGraphicsTextItem hintText;
    bool hintBarHidden;

    std::set<int> keyPressed;

    QLabel *getLabel(QString &input);
    void createLayout();
    void createBoard();
    void addMovingItems();
    void createHintText();
    QPushButton *initButton(const char *myString);
    bool gameStopped();
    void stopGhosts();
    void pacmanNoticed();
    void addLives();
    void resetLives();
    void levelPassed();
public:
    explicit Level(int w, int h, QWidget *parent = 0);
signals:
    void coinWasEaten();
public slots:
    void hideHintBar();
    void resetMovingObjects();
    void pacmanPosPropagation();
    void restartGhost(Ghost *);
    void waitForIt(int);
    void increaseScore();
    void pauseGame();
    void startGame();
    void managePausedGame();
    void returnToMainMenu();
    void startGhosts();
    void endGame();
    void positionCheck();
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void managePressedKeys();

};

#endif // LEVEL_H
