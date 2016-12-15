#include "level.h"

#define BOARD_SIZE 26
#define PACMAN_IMAGE_WIDTH 200
#define BOX_SIZE (int)(h*(double)19/20)
#define SUPERCOIN 4
#define WALL 0
#define COIN 1
#define EMPTY 3
#include <memory>
char boolBoard[BOARD_SIZE][BOARD_SIZE] =   {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
                                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//2
                                        {4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 4},//3
                                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//4
                                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//5
                                        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},//6
                                        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},//7
                                        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},//8
                                        {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},//9
                                        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},//10
                                        {1, 0, 0, 0, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 0, 0, 0, 0, 1},//11
                                        {1, 1, 1, 1, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 1, 1, 1, 1},//12
                                        {0, 0, 0, 1, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 1, 0, 0, 0},//13
                                        {3, 3, 0, 1, 1, 1, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 1, 1, 1, 1, 0, 3, 3},//14
                                        {0, 0, 0, 1, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 1, 0, 0, 0},//15
                                        {1, 1, 1, 1, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 0, 1, 1, 1, 1},//16
                                        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},//17
                                        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},//18
                                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//19
                                        {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},//20
                                        {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},//21
                                        {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1},//22
                                        {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},//23
                                        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},//24
                                        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},//25
                                        {1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1}};//26
Level::Level(int w, int h, QWidget *parent) : QWidget(parent), pacmanLifes(3),
    pause(initButton("Pause")), start(initButton("Start")), mainMenu(initButton("Main Menu")),
    scoreLcd(std::make_unique<QLCDNumber>(5, this)), layout(std::make_unique<QGridLayout>(this)),
    board(std::make_unique<QGraphicsScene>(-5, -5, BOX_SIZE -5, BOX_SIZE -5, this)), view(std::make_unique<QGraphicsView>()),
    lifeBoxes(std::make_unique<QHBoxLayout>(this)), SQUARE_SIZE((int)(BOX_SIZE/(double)BOARD_SIZE)),
    mainPacman(std::make_unique<Pacman>(13, 21, SQUARE_SIZE)), stopOrNot(false), blueGhost(11, 12, SQUARE_SIZE, "blue"),
    redGhost(12, 12, SQUARE_SIZE, "red"), orangeGhost(13, 12, SQUARE_SIZE, "orange"), pinkGhost(14, 12, SQUARE_SIZE, "pink")
{
    resize(w, h);
    view.get()->setFixedSize(BOX_SIZE, BOX_SIZE);
//    view.get()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view.get()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.get()->setStyleSheet("background-color: #113F73;"
                            "background-clip: padding;"
                            "color: #0B4485;"
                            "border-style: groove ;"
                            "border-radius: 5px;"
                            "border-width: 0px;"
                            "margin: 0px;"
                            );

    scoreLcd.get()->setFrameShape(QFrame::NoFrame);
    scoreLcd.get()->setStyleSheet("color: rgb(255, 230, 255)");
    for(unsigned int i = 0; i < pacmanLifes; i++) {
        QWidget *tempPacman = new QWidget(this);
        tempPacman->setMaximumSize(1.5 * SQUARE_SIZE, 1.5 *  SQUARE_SIZE);
        tempPacman->setStyleSheet("QWidget {border-image: url(:/images/pacmanicon.ico) 0 0 0 0 stretch stretch;}");
        lifeBoxes.get()->addWidget(tempPacman);
    }

    createLayout();

    layout.get()->setColumnMinimumWidth(1, BOX_SIZE);
    setLayout(layout.get());
    view.get()->setScene(board.get());
    connect(pause.get(), SIGNAL(pressed()), this, SLOT(pauseGame()) );
    connect(start.get(), SIGNAL(pressed()), this, SLOT(startGame()) );
    connect(mainMenu.get(), SIGNAL(pressed()), this, SLOT(returnToMainMenu()) );
    connect(mainPacman.get(), SIGNAL(scoreChanged()), this, SLOT(increaseScore()));
    connect(mainPacman.get(), SIGNAL(pauseGame()), this, SLOT(managePausedGame()) );
    //connect(mainPacman.get(), SIGNAL(stopGhosts(int)), this, SLOT(waitForIt(int)) );
    createBoard();
    addMovingItems();
    pauseGame();
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

void Level::waitForIt(int interval)
{
    QTimer tempTimer();


}
void Level::increaseScore()
{
    scoreLcd.get()->display(mainPacman.get()->getScore());
}

void Level::pauseGame()
{
    if(gameStopped())
        return;
    mainPacman.get()->stopMoving();
    stopGhosts();
    stopOrNot = true;
}

void Level::startGame()
{
    if(!gameStopped())
        return;
    mainPacman.get()->startMoving();
    startGhosts();
    stopOrNot = false;
}

void Level::managePausedGame()
{
    if(gameStopped())
        startGame();
    else pauseGame();
}

void Level::returnToMainMenu()
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
    layout.get()->addWidget(getLabel(tr("SCORE:")), 1, 0);
    layout.get()->addWidget(scoreLcd.get(), 2, 0);
    layout.get()->addWidget(static_cast<QWidget*>(view.get()), 0, 1, 6, 1);
    std::unique_ptr<QVBoxLayout>tempLayout2(new QVBoxLayout);
    tempLayout2.get()->addWidget(getLabel(tr("LIVES:")));
    tempLayout2.get()->addLayout(lifeBoxes.get());
    tempLayout2.get()->addWidget(getLabel(tr("OPTIONS:")));
    tempLayout2.get()->addWidget(pause.get());
    tempLayout2.get()->addWidget(start.get());
    tempLayout2.get()->addWidget(mainMenu.get());
    layout.get()->addLayout(tempLayout2.get(), 0, 2, 6, 1);
    tempLayout2.release();
//    layout->addWidget(getLabel(tr("LIVES:")), 0, 2 );
//    layout->addLayout(lifeBoxes, 1, 2);
//    layout->addWidget(getLabel(tr("OPTIONS:")), 2, 2 );
//    layout->addWidget(pause, 3, 2);
//    layout->addWidget(start, 4, 2);
    //    layout->addWidget(mainMenu, 5, 2);
}

void Level::createBoard()
{
    for(unsigned int x = 0; x < BOARD_SIZE; x++) {
        for(unsigned y = 0; y < BOARD_SIZE; y++) {
            switch(boolBoard[y][x]) {
            case WALL:
                boardArea[x][y] = new Wall(x, y, SQUARE_SIZE);
                break;
            case COIN:
                boardArea[x][y] = new Coin(x, y, SQUARE_SIZE);
                break;
            case SUPERCOIN:
                boardArea[x][y] = new SuperCoin(x, y, SQUARE_SIZE);
                break;
            default:
                boardArea[x][y] = nullptr;
            }
            if(boardArea[x][y] != nullptr) {
                boardArea[x][y]->setAcceptedMouseButtons(0);
                board.get()->addItem(boardArea[x][y]);
            }
        }
    }
}

void Level::addMovingItems()
{
    qDebug() <<"spucha";
    board.get()->addItem(mainPacman.get());
    mainPacman.get()->setFocus();
    mainPacman.get()->grabKeyboard();
    mainPacman.get()->grabMouse();
    board.get()->addItem(&redGhost);
    board.get()->addItem(&blueGhost);
    board.get()->addItem(&orangeGhost);
    board.get()->addItem(&pinkGhost);
//    pauseGame();
}

void Level::stopGhosts()
{
    blueGhost.stopMoving();
    redGhost.stopMoving();
    orangeGhost.stopMoving();
    pinkGhost.stopMoving();
}

void Level::startGhosts()
{
    redGhost.startMoving();
    blueGhost.startMoving();
    orangeGhost.startMoving();
    pinkGhost.startMoving();
}

bool Level::gameStopped()
{
    return stopOrNot;
}
