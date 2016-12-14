
#include "gamearea.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include "wall.h"
#include "gamearea.h"
#include "coin.h"
#include "supercoin.h"
#include "movingobject.h"
#include "pacman.h"
#define SUPERCOIN 4
#define WALL 0
#define COIN 1
#define EMPTY 3
#define BOARD_SIZE 26
char board[BOARD_SIZE][BOARD_SIZE] =   {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
                                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//2
                                        {4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 4},//3
                                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//4
                                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//5
                                        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},//6
                                        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},//7
                                        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},//8
                                        {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},//9
                                        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},//10
                                        {0, 1, 0, 0, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 0, 0, 0, 1, 0},//11
                                        {0, 1, 1, 1, 0, 0, 1, 0, 0, 3, 0, 0, 3, 3, 0, 0, 3, 0, 0, 1, 0, 0, 1, 1, 1, 0},//12
                                        {0, 0, 0, 1, 0, 0, 1, 0, 0, 3, 0, 3, 3, 3, 3, 0, 3, 0, 0, 1, 0, 0, 1, 0, 0, 0},//13
                                        {3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3},//14
                                        {0, 0, 0, 1, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 1, 0, 0, 0},//15
                                        {0, 1, 1, 1, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 0, 0, 1, 1, 1, 0},//16
                                        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},//17
                                        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},//18
                                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//19
                                        {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},//20
                                        {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},//21
                                        {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1},//22
                                        {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},//23
                                        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},//24
                                        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},//25
                                        {1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1}};//26
GameArea::GameArea(int w, int h, QWidget *parent) : QGraphicsScene(parent),SQUARE_SIZE((int)(h/(double)BOARD_SIZE)),
    mainPacman(new Pacman(0, 0, SQUARE_SIZE))
{

    setSceneRect(-5,-5, w + 5, h + 5);

    for(unsigned int x = 0; x < BOARD_SIZE; x++) {
        for(unsigned y = 0; y < BOARD_SIZE; y++) {
            switch(board[y][x]) {
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
                addItem(boardArea[x][y]);
            }
        }
    }
    addItem(mainPacman);
    mainPacman->setFocus();
    mainPacman->grabKeyboard();
    mainPacman->grabMouse();
}
