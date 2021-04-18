#ifndef RENDERER
#define RENDERER

#include "move.h"
#include "ship.h"
#include "asteroid.h"

class Renderer
{
public:
    void drawAsteroid(float x, float y, float angle, float size);
    void drawShip(float x, float y, float angle);
    void drawBullet(float x, float y);
    void drawArena(int width, int height, int wChange, int hChange, Ship s);
    void drawBullet(float x, float y, float size);
};

#endif