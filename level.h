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
    QPushButton *pause;
    QPushButton *start;
    QPushButton *mainMenu;
    GameArea * board;
    QLabel *getLabel(QString &input);
    QLCDNumber *scoreLcd;
public:
    explicit Level(QWidget *parent = 0);

signals:

public slots:

};

#endif // LEVEL_H
