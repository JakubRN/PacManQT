#include "level.h"
#include <QSizePolicy>
#include <QStyle>
#include <QDebug>
#include <QLCDNumber>
#define BOARD_SIZE 26
#define SQUARE_SIZE (int)(h/(double)BOARD_SIZE)
#define PACMAN_IMAGE_WIDTH 200
#define BOX_SIZE (int)(h*(double)19/20)

Level::Level(int w, int h, QWidget *parent) : QWidget(parent), pacmanLifes(3),
    pause(initButton("Pause")), start(initButton("Start")), mainMenu(initButton("Main Menu")),
    scoreLcd(new QLCDNumber(5, this)), layout(new QGridLayout(this)),
    board(new GameArea(BOX_SIZE - 10, BOX_SIZE -10, this)), view(new QGraphicsView(board)),
    lifeBoxes(new QHBoxLayout(this))
{
    resize(w, h);

    view->setFixedSize(BOX_SIZE, BOX_SIZE);
    //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background-color: #0B4485;"
                            "background-clip: padding;"
                            "color: #0B4485;"
                            "border-style: groove ;"
                            "border-radius: 5px;"
                            "border-width: 0px;"
                            "margin: 0px;"
                            );

    scoreLcd->setFrameShape(QFrame::NoFrame);
    scoreLcd->setStyleSheet("color: rgb(255, 230, 255)");
    for(unsigned int i = 0; i < pacmanLifes; i++) {
        QWidget *tempPacman = new QWidget(this);
        tempPacman->setMaximumSize(SQUARE_SIZE, SQUARE_SIZE);
        tempPacman->setMaximumSize(SQUARE_SIZE, SQUARE_SIZE);
        tempPacman->setStyleSheet("QWidget {border-image: url(:/images/pacmanicon.ico) 0 0 0 0 stretch stretch;}");
        lifeBoxes->addWidget(tempPacman);
    }

    createLayout();
    layout->setColumnMinimumWidth(1, BOX_SIZE);
    setLayout(layout);

    connect(board->mainPacman, SIGNAL(scoreChanged()), this, SLOT(increaseScore()));
    connect(pause, SIGNAL(pressed()), this, SLOT(pauseGame()) );

}

QPushButton *Level::initButton(const char *myString)
{
    QPushButton *button = new QPushButton(tr(myString), this);
    button->setStyleSheet("background-color: #265285;"
                         "color: rgb(255, 230, 255) ;"
                         "border-style: outset;"
                         "border-width: 5px;"
                         "border-radius: 15px;"
                         "border-color: #38280A;"
                         "font: bold 14px;"
                         "min-width: 10em;"
                         "padding: 6px;"
                          );
    button->setFocusPolicy(Qt::NoFocus);
    return button;
}
void Level::increaseScore()
{
    scoreLcd->display(board->mainPacman->score);
}

void Level::pauseGame()
{
    exit(0);
}

QLabel *Level::getLabel(QString &input)
{
    QLabel *lbl = new QLabel(input, this);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    lbl->setFont(QFont("font: Times New Roman", 24, QFont::Bold));
    lbl->setScaledContents(true);
    lbl->setStyleSheet("color: #855500");
    return lbl;
}

void Level::createLayout()
{
    layout->addWidget(getLabel(tr("SCORE:")), 1, 0);
    layout->addWidget(scoreLcd, 2, 0);
    layout->addWidget(view, 0, 1, 6, 1);
    QVBoxLayout *tempLayout2 = new QVBoxLayout;
    tempLayout2->addWidget(getLabel(tr("LIVES:")));
    tempLayout2->addLayout(lifeBoxes);
    tempLayout2->addWidget(getLabel(tr("OPTIONS:")));
    tempLayout2->addWidget(pause);
    tempLayout2->addWidget(start);
    tempLayout2->addWidget(mainMenu);
    layout->addLayout(tempLayout2, 0, 2, 6, 1);
//    layout->addWidget(getLabel(tr("LIVES:")), 0, 2 );
//    layout->addLayout(lifeBoxes, 1, 2);
//    layout->addWidget(getLabel(tr("OPTIONS:")), 2, 2 );
//    layout->addWidget(pause, 3, 2);
//    layout->addWidget(start, 4, 2);
//    layout->addWidget(mainMenu, 5, 2);
}
