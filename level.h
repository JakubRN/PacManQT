#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QSizePolicy>
#include "gamearea.h"

class Level : public QWidget
{
    Q_OBJECT
    QGridLayout *layout;
    QPushButton *pause;
    QPushButton *start;
    QPushButton *mainMenu;
    GameArea * board;
    QLabel *getLabel(QString &input);
    QLCDNumber *scoreLcd;
public:
    explicit Level(int w, int h, QWidget *parent = 0);
    QPushButton *initButton(const char *myString);

signals:

public slots:
    void pauseGame();

};

#endif // LEVEL_H
