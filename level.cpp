#include "level.h"
#include <QGraphicsTextItem>
#define BOARD_SIZE 26
#define PACMAN_IMAGE_WIDTH 200
#define BOX_SIZE (int)(h*(double)19/20)
#define SUPERCOIN 4
#define WALL 0
#define COIN 1
#define EMPTY 3
#include <memory>
#include <QTextBlockFormat>
#include <QTextCursor>
#define START_POS(arg1, arg2) arg1, arg2
#define BLUE_GHOST_START START_POS(11, 12)
#define RED_GHOST_START START_POS(12, 12)
#define ORANGE_GHOST_START START_POS(13, 12)
#define PINK_GHOST_START START_POS(14, 12)
#define PACMAN_START_POS START_POS(13, 21)
#define RESET_TIME 1000

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
    board(std::make_unique<QGraphicsScene>(-5, -5, BOX_SIZE -5, BOX_SIZE -5, this)),
    view(std::make_unique<QGraphicsView>()),
    lifeBoxes(std::make_unique<QHBoxLayout>(this)), SQUARE_SIZE((int)(BOX_SIZE/(double)BOARD_SIZE)),
    mainPacman(std::make_unique<Pacman>(PACMAN_START_POS, SQUARE_SIZE)), stopOrNot(false),
    blueGhost(std::make_unique<Ghost>(BLUE_GHOST_START, SQUARE_SIZE, "blue")),
    redGhost(std::make_unique<Ghost>(RED_GHOST_START, SQUARE_SIZE, "red")),
             orangeGhost(std::make_unique<Ghost>(ORANGE_GHOST_START, SQUARE_SIZE, "orange")),
                         pinkGhost(std::make_unique<Ghost>(PINK_GHOST_START, SQUARE_SIZE, "pink")),
                         ghostTimer(), gameOver(false), resetTimer(), pacmans(3), hintText("PRESS SPACE TO START"), hintBarHidden(false), keyPressed()
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
    resetTimer.setSingleShot(true);
    connect(&resetTimer, SIGNAL(timeout()), this, SLOT(resetMovingObjects()));

    ghostTimer.setSingleShot(true);
    connect(&ghostTimer, SIGNAL(timeout()), this, SLOT(startGhosts()));

    scoreLcd.get()->setFrameShape(QFrame::NoFrame);
    scoreLcd.get()->setStyleSheet("color: rgb(255, 230, 255)");


    addLives();
    createLayout();
    layout.get()->setColumnMinimumWidth(1, BOX_SIZE);
    setLayout(layout.get());
    view.get()->setScene(board.get());
    createBoard();
    addMovingItems();
    createHintText();


    connect(pause.get(), SIGNAL(pressed()), this, SLOT(pauseGame()) );
    connect(start.get(), SIGNAL(pressed()), this, SLOT(startGame()) );
    connect(mainMenu.get(), SIGNAL(pressed()), this, SLOT(returnToMainMenu()) );
    connect(mainPacman.get(), SIGNAL(scoreChanged()), this, SLOT(increaseScore()));
    connect(mainPacman.get(), SIGNAL(stopGhosts(int)), this, SLOT(waitForIt(int)) );
    connect(mainPacman.get(), SIGNAL(gameOver()), this, SLOT(endGame()));
    connect(mainPacman.get(), SIGNAL(ghostEaten(Ghost*)), this, SLOT(restartGhost(Ghost*)));
    connect(mainPacman.get(), SIGNAL(positionChanged()), this, SLOT(positionCheck()));
    connect(blueGhost.get(), SIGNAL(pacmanLost()), this, SLOT(pacmanPosPropagation()));
    connect(redGhost.get(), SIGNAL(pacmanLost()), this, SLOT(pacmanPosPropagation()));
    connect(orangeGhost.get(), SIGNAL(pacmanLost()), this, SLOT(pacmanPosPropagation()));
    connect(pinkGhost.get(), SIGNAL(pacmanLost()), this, SLOT(pacmanPosPropagation()));

    setFocus();
    grabKeyboard();
    pauseGame();
}

void Level::hideHintBar()
{
    if(!hintBarHidden) {

        hintText.setPlainText("");
        hintBarHidden = true;
    }
}

void Level::resetMovingObjects()
{
    blueGhost.get()->resetGhost(BLUE_GHOST_START);
    redGhost.get()->resetGhost(RED_GHOST_START);
    orangeGhost.get()->resetGhost(ORANGE_GHOST_START);
    pinkGhost.get()->resetGhost(PINK_GHOST_START);
    mainPacman.get()->resetPacman(PACMAN_START_POS);
    gameOver = false;
    stopOrNot = false;
}

void Level::pacmanPosPropagation()
{
    blueGhost.get()->pacmanHidden();
    redGhost.get()->pacmanHidden();
    orangeGhost.get()->pacmanHidden();
    pinkGhost.get()->pacmanHidden();
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
    stopGhosts();
    ghostTimer.start(interval);
}
void Level::increaseScore()
{
    scoreLcd.get()->display(mainPacman.get()->getScore());
    static unsigned int x = 0;
    for(; x < BOARD_SIZE; x++) {
        for(auto y = 0; y < BOARD_SIZE; y++) {
            if(dynamic_cast<Coin *>(boardArea[x][y]) != NULL) {
                if(boardArea[x][y]->isActive())
                    return;
            }
        }
    }
    levelPassed();
}

void Level::pauseGame()
{
    if(!gameStopped()) {
        mainPacman.get()->stopMoving();
        if(mainPacman.get()->pacmanChangingColor()) {
            ghostTimer.stop();
        }
        else stopGhosts();
        stopOrNot = true;
    }
}

void Level::startGame()
{
    if(gameStopped()) {
        mainPacman.get()->startMoving();
        if(mainPacman.get()->pacmanChangingColor()) {
            ghostTimer.start(mainPacman.get()->getRemainingTime());
        }
        else startGhosts();
        stopOrNot = false;
    }
}

void Level::managePausedGame()
{
    if(gameOver || mainPacman.get()->pacmanIsResetting)
        return;
    else if(gameStopped()) {
        hideHintBar();
        startGame();
    }
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
    board.get()->addItem(mainPacman.get());
    board.get()->addItem(redGhost.get());
    board.get()->addItem(blueGhost.get());
    board.get()->addItem(orangeGhost.get());
    board.get()->addItem(pinkGhost.get());
    //    pauseGame();
}

void Level::createHintText()
{
    board.get()->addItem(&hintText);
    hintText.setFont(QFont("Courier", 60, 10));
    hintText.adjustSize();
    hintText.setPos(0, view.get()->height()/20);
    hintText.setTextWidth(board.get()->width());
    hintText.setDefaultTextColor(Qt::white);
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QTextCursor cursor = hintText.textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    cursor.clearSelection();
    hintText.setTextCursor(cursor);
}

void Level::stopGhosts()
{
    blueGhost.get()->stopMoving();
    redGhost.get()->stopMoving();
    orangeGhost.get()->stopMoving();
    pinkGhost.get()->stopMoving();
}

void Level::pacmanNoticed()
{
    blueGhost.get()->pacmanNoticed(mainPacman.get()->getX(),
                                   mainPacman.get()->getY(), mainPacman.get()->getRedState());
    redGhost.get()->pacmanNoticed(mainPacman.get()->getX(),
                                  mainPacman.get()->getY(), mainPacman.get()->getRedState());
    orangeGhost.get()->pacmanNoticed(mainPacman.get()->getX(),
                                     mainPacman.get()->getY(), mainPacman.get()->getRedState());
    pinkGhost.get()->pacmanNoticed(mainPacman.get()->getX(),
                                   mainPacman.get()->getY(), mainPacman.get()->getRedState());
}

void Level::addLives()
{
    for(unsigned int i = 0; i < pacmanLifes; i++) {
        std::unique_ptr<QWidget> tempPacman(new QWidget());
       pacmans.at(i) = tempPacman.get();
        tempPacman.get()->setMaximumSize(1.5 * SQUARE_SIZE, 1.5 *  SQUARE_SIZE);
        tempPacman.get()->setStyleSheet("QWidget {border-image: url(:/images/pacmanicon.ico) 0 0 0 0 stretch stretch;}");
        lifeBoxes.get()->addWidget(tempPacman.get());
        tempPacman.release();
    }
}

void Level::resetLives()
{
    //QWidget *child;
    lifeBoxes.get()->removeWidget(pacmans[pacmanLifes]);
    delete pacmans[pacmanLifes];

    //addLives();
}

void Level::levelPassed()
{
    pauseGame();
    //mainPacman.get()->clearFocus();
    //mainPacman.get()->ungrabKeyboard();
    hintText.setPlainText("YOU PASSED THE FIRST LEVEL!");
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QTextCursor cursor = hintText.textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    cursor.clearSelection();
    hintText.setTextCursor(cursor);
}

void Level::restartGhost(Ghost *ghost)
{
    ghost->resetGhost(13, 12);
}

void Level::startGhosts()
{
    redGhost.get()->startMoving();
    blueGhost.get()->startMoving();
    orangeGhost.get()->startMoving();
    pinkGhost.get()->startMoving();
}

void Level::endGame()
{
    pauseGame();
    mainPacman.get()->clearFocus();
    gameOver = true;
    if(pacmanLifes == 1) {
        std::unique_ptr<QGraphicsTextItem> finalText(new QGraphicsTextItem("GAME OVER"));
        board.get()->addItem(finalText.get());
        finalText.get()->setFont(QFont("Courier", 100, 3));
        finalText.get()->adjustSize();
        finalText.get()->setPos((board.get()->width() - finalText.get()->textWidth())/2, board.get()->height()/2 - 100);
        finalText.get()->setDefaultTextColor(Qt::red);
        finalText.release();
    }
    else {
        pacmanLifes--;
        resetLives();
        qDebug() << "co jest kurwa";
        resetTimer.start(RESET_TIME);
    }

    //    mainPacman.get()->setFocusPolicy(Qt::NoFocus);
}

void Level::positionCheck()
{
    int pacmanX = mainPacman.get()->getX();
    int pacmanY = mainPacman.get()->getY();
    int tempX = pacmanX;
    while(tempX != BOARD_SIZE && boolBoard[pacmanY][tempX] != WALL)
        tempX++;
    QList <QGraphicsItem *> elementList = board.get()->items((pacmanX + 1) * SQUARE_SIZE,
                            pacmanY * SQUARE_SIZE, (tempX - pacmanX) * SQUARE_SIZE,
                    SQUARE_SIZE, Qt::IntersectsItemShape, Qt::DescendingOrder);
    for(auto &a : elementList ) {
        if(typeid(*a) == typeid(Ghost)) {
            pacmanNoticed();
            return;
        }
    }
    tempX = pacmanX;
    while(tempX != 0 && boolBoard[pacmanY][tempX] != WALL)
        tempX--;
    elementList = board.get()->items(tempX * SQUARE_SIZE, pacmanY * SQUARE_SIZE,
                        (pacmanX - tempX) * SQUARE_SIZE, SQUARE_SIZE,
                                     Qt::IntersectsItemShape, Qt::DescendingOrder);
    for(auto &a : elementList ) {
        if(typeid(*a) == typeid(Ghost)) {
            pacmanNoticed();
            return;
        }
    }
    int tempY = pacmanY;
    while(tempY != 0 && boolBoard[tempY][pacmanX] != WALL)
        tempY--;
    elementList = board.get()->items(pacmanX * SQUARE_SIZE, tempY * SQUARE_SIZE, SQUARE_SIZE,
                                     (pacmanY - tempY) * SQUARE_SIZE, Qt::IntersectsItemShape, Qt::DescendingOrder);
    for(auto &a : elementList ) {
        if(typeid(*a) == typeid(Ghost)) {
            pacmanNoticed();
            return;
        }
    }
    tempY = pacmanY;
    while(tempY != BOARD_SIZE && boolBoard[tempY][pacmanX] != WALL)
        tempY++;
    elementList = board.get()->items(pacmanX * SQUARE_SIZE, (pacmanY + 1) * SQUARE_SIZE, SQUARE_SIZE,
                                     (tempY - pacmanY) * SQUARE_SIZE, Qt::IntersectsItemShape, Qt::DescendingOrder);
    for(auto &a : elementList ) {
        if(typeid(*a) == typeid(Ghost)) {
            pacmanNoticed();
            return;
        }
    }
}

void Level::keyPressEvent(QKeyEvent *event)
{
    keyPressed.insert(event->key());
    managePressedKeys();
}

void Level::keyReleaseEvent(QKeyEvent *event)
{
    keyPressed.erase(event->key());
}

void Level::managePressedKeys()
{
    for(auto i : keyPressed){
        switch(i) {
        case Qt::Key_Left:
            mainPacman.get()->setNextDirection(possibleDirections::left);
            break;
        case Qt::Key_Right:
            mainPacman.get()->setNextDirection(possibleDirections::right);
            break;
        case Qt::Key_Up:
            mainPacman.get()->setNextDirection(possibleDirections::up);
            break;
        case Qt::Key_Down:
            mainPacman.get()->setNextDirection(possibleDirections::down);
            break;
        case Qt::Key_Space:
            managePausedGame();
        }
    }
}

bool Level::gameStopped()
{
    return stopOrNot;
}
