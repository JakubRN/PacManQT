#include "level.h"
#include <QSizePolicy>
#include <QStyle>
#include <QDebug>

Level::Level(int w, int h, QWidget *parent) : QWidget(parent)
{
    //setFrameStyle(QFrame::StyledPanel);
    resize(w, h);
    setStyleSheet("border-width: 0px;"
                  "padding: 0px;"
                  "margin: 0px;"

                  );

    qDebug() << this->width() << this->height();

    board = new GameArea(h*15/16 - 10, h*15/16 - 10, this);
    qDebug() << board->width() <<"\t\t" << board->height() << w;

    QGraphicsView *view = new QGraphicsView(board);
    view->setFixedSize(h*15/16, h*15/16);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background-color: #0B4485;"
                            "background-clip: padding;"
                            "color: #0B4485;"
                            "border-style: groove ;"
                            "border-radius: 5px;"
                            "border-width: 0px;"
                            "margin: 0px;"
                            );

    pause = initButton("Pause");
    start = initButton("Start");
    mainMenu = initButton("Main Menu");
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setFrameShape(QFrame::NoFrame);
    scoreLcd->setStyleSheet("color: rgb(255, 230, 255)");

    layout = new QGridLayout(this);
    layout->addWidget(getLabel(tr("SCORE:")), 0, 0);
    layout->addWidget(scoreLcd, 1, 0);

    layout->addWidget(view, 0, 1, 6, 6);

    layout->addWidget(getLabel(tr("LIVES:")), 0, 7 );
    layout->addWidget(getLabel(tr("OPTIONS:")), 2, 7 );
    layout->addWidget(pause, 3, 7);
    layout->addWidget(start, 4, 7);
    layout->addWidget(mainMenu, 5, 7);

    connect(pause, SIGNAL(pressed()), this, SLOT(pauseGame()) );
    setLayout(layout);
    qDebug() << view->width() << view->height() << "My view";
    qDebug() << board->width() << board->height() << "My board";
}

QPushButton *Level::initButton(const char *myString)
{
    QPushButton *button = new QPushButton(tr(myString), this);
    button->setFocusPolicy(Qt::StrongFocus);
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
    return button;
}

void Level::pauseGame()
{
    exit(0);
}

QLabel *Level::getLabel(QString &input)
{
    QLabel *lbl = new QLabel(input);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    lbl->setFont(QFont("font: Times New Roman", 24, QFont::Bold));
    lbl->setScaledContents(true);
    lbl->setStyleSheet("color: #855500");
    return lbl;
}
