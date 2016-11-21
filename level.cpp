#include "level.h"
#include <QSizePolicy>
#include <QStyle>

Level::Level(QWidget *parent) : QWidget(parent)
{
    //setFrameStyle(QFrame::StyledPanel);
    setStyleSheet("border-width: 0px;"
                  "padding: 0px;"
                  "margin: 0px;"

                  );


    scoreLcd = new QLCDNumber(5);
    scoreLcd->setFrameShape(QFrame::NoFrame);
    scoreLcd->setStyleSheet("color: rgb(255, 230, 255)");
    board = new GameArea;

    pause = initButton("Pause");
    start = initButton("Pause");
    mainMenu = initButton("Main Menu");

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

QPushButton *Level::initButton(const char *myString)
{
    QPushButton *button = new QPushButton(tr(myString));
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
                         "pressed {"
                         "color: yellow;"
                         "background-color: blue;"
                         "}"
                          );
    return button;
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
