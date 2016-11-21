#include "level.h"
#include <QSizePolicy>
#include <QStyle>

Level::Level(QWidget *parent) : QWidget(parent)
{
    //setFrameStyle(QFrame::StyledPanel);
    setStyleSheet("color: blue; background-color: ffffff;"

                  );


    scoreLcd = new QLCDNumber(5);
    scoreLcd->setFrameShape(QFrame::NoFrame);
    scoreLcd->setStyleSheet("color: #ffffff");
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
    button->setFocusPolicy(Qt::NoFocus);
    button->setStyleSheet("background-color: rgb(160, 0, 0);"
                         "color:rgb(0, 0, 80) ;"
                         "border-style: outset;"
                         "border-width: 2px;"
                         "border-radius: 10px;"
                         "border-color: rgb(80, 0, 0);"
                         "font: bold 14px;"
                         "min-width: 10em;"
                         "padding: 6px;"
                          "selection-color: yellow;"
                          );
    return button;
}

QLabel *Level::getLabel(QString &input)
{
    QLabel *lbl = new QLabel(input);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    lbl->setFont(QFont("font: Times New Roman", 24, QFont::Light));
    lbl->setScaledContents(true);
    lbl->setStyleSheet("color: #ffffff");
    return lbl;
}
