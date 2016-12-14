#include "supercoin.h"
#define RADIUS ((double)size/2)

SuperCoin::SuperCoin(unsigned int x, unsigned int y, int size, GameObject *parent) : Coin(x, y, size, parent)
{
    radius = RADIUS;
}
