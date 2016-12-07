
#include "gamearea.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include "wall.h"
#include "gamearea.h"
#define BOARD_SIZE 26
#define SQUARE_SIZE (int)(h/(double)BOARD_SIZE)
#define PACMAN_IMAGE_WIDTH 200
char board[BOARD_SIZE][BOARD_SIZE] =   {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
                                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//2
                                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//3
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
                                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};//26
                GameArea::GameArea(int w, int h, QWidget *parent) : QGraphicsScene(parent)
{

    setSceneRect(-5,-5, w + 5, h + 5);
    qDebug() << this->width() << "spucha"<< SQUARE_SIZE << this->height();

    Pacman = new QGraphicsPixmapItem();
    Pacman->setPixmap(QPixmap(":/images/Pac-man.gif"));
    Pacman->setPos(0,0);
    Pacman->setScale((double)SQUARE_SIZE/PACMAN_IMAGE_WIDTH);

    GameObject *gameObject[BOARD_SIZE][BOARD_SIZE];
    for(unsigned int x = 0; x < BOARD_SIZE; x++) {
        for(unsigned y = 0; y < BOARD_SIZE; y++) {
            if(board[y][x] == 0){
            Wall *temp = new Wall(x, y, SQUARE_SIZE);
            gameObject[x][y] = temp;
            addItem(gameObject[x][y]);
            }
            if(board[y][x] == 1) {
                QGraphicsEllipseItem *temp = new QGraphicsEllipseItem(SQUARE_SIZE * x + SQUARE_SIZE/2, SQUARE_SIZE * y + SQUARE_SIZE/2,
                                                                        SQUARE_SIZE/4, SQUARE_SIZE/4);
                temp->setBrush((*new QBrush(Qt::yellow)));
                //gameObject[x][y] = temp;
                addItem(temp);
            }
        }
    }
    addItem(Pacman);

}
