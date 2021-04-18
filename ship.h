#ifndef SHIP
#define SHIP

#include "keys.h"
#include "move.h"
#include "vector.h"
#include "settings.h"
#include <cmath>

class Renderer;

class Ship
{
private:
    Move move_;
public:
    Ship();
    void tick(Keys, Settings settings, Vector v);
    void draw(Renderer &, int screen_width, int screen_height);

    float angel_;    
    float vx;
    float vy;
    float x = 150.0f;
    float y = 150.0f;
    int radius;
    bool isFlying = false;
    float velLimit = 5.0f;
    float accel = 1.0f;
    bool isFiring = false;
    float rateOfFire = 0.25;
    float nextBullet = 0;
    };

#endif