#ifndef ARENA
#define ARENA

#include "vector.h"
#include "renderer.h"
#include "settings.h"
#include "ship.h"

class Renderer;

class Arena
{
public:
    Arena();
    void draw(Renderer &, Settings s, Ship ship);
};

#endif