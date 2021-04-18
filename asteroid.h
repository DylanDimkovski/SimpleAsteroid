#ifndef ASTEROID
#define ASTEROID

#include "keys.h"
#include "vector.h"
#include "renderer.h"
#include "vector"

class Asteroid
{
public:
    Asteroid();
    void draw(Renderer &, std::vector<Asteroid> &asteroids, Ship s);

    std::vector<float> pointArray;
    bool insideArena = false;
    float angle;
    float vx = 5.0;
    float vy = 0.0;
    float vr = 0.5;
    float x;
    float y;
    float size;
    int count = 0;
    int radius;
    float health = 100;
    float points = 5;
    int pointSize = 9;
};

#endif