#include "level.h"
#include <QSizePolicy>

Level::Level(QWidget *parent) : QWidget(parent)
{
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setFrameShape(QFrame::NoFrame);
    board = new GameArea;
    pause = new QPushButton(tr("Pause"));
    pause->setFocusPolicy(Qt::NoFocus);
    //pause->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    start = new QPushButton(tr("Start"));
    start->setFocusPolicy(Qt::NoFocus);
    mainMenu = new QPushButton(tr("Main Menu"));
    mainMenu->setFocusPolicy(Qt::NoFocus);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(getLabel(tr("SCORE:")), 0, 0);
    layout->addWidget(scoreLcd, 1, 0);
    layout->addWidget(board, 0, 1, 6, 6);
    layout->addWidget(getLabel(tr("LIVES:")), 0, 7 );

    layout->addWidget(getLabel(tr("OPTIONS:")), 2, 7 );
    layout->addWidget(pause, 3, 7);
    layout->addWidget(start, 4, 7);
    layout->addWidget(mainMenu, 5, 7);
    setLayout(layout);
}

QLabel *Level::getLabel(QString &input)
{
    QLabel *lbl = new QLabel(input);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    lbl->setFont(QFont("font: Times New Roman", 24, QFont::Light));
    lbl->setScaledContents(true);
    return lbl;
}
