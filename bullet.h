#ifndef BULLET
#define BULLET

#include "renderer.h"

class Bullet
{
public:
    Bullet();
    void draw(Renderer &, Bullet b);

    int x;
    int y;
    int vx = 20;
    int vy = 20;
    int size = 15;
    int damage = 30;
    bool isInArena;
};

#endif