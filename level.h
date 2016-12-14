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
#include "gamearea.h"
#include <vector>
#include <QPalette>

class Level : public QWidget
{
    Q_OBJECT
    unsigned int pacmanLifes;
    QPushButton *pause;
    QPushButton *start;
    QPushButton *mainMenu;
    QLCDNumber *scoreLcd;
    QGridLayout *layout;
    GameArea * board;
    QGraphicsView *view;
    QHBoxLayout *lifeBoxes;

    QLabel *getLabel(QString &input);
    void createLayout();
    int Score;
public:
    explicit Level(int w, int h, QWidget *parent = 0);
    QPushButton *initButton(const char *myString);

signals:
    void coinWasEaten();
public slots:
    void increaseScore();
    void pauseGame();

};

#endif // LEVEL_H
