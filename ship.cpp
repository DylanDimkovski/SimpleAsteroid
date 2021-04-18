#define _USE_MATH_DEFINES

#include <cmath>
#include "ship.h"
#include "renderer.h"

Ship::Ship(): angel_(90), vx(0), vy(0)
{}

void Ship::tick(Keys keys, Settings settings, Vector acel)
{
    if (keys[KEY_LEFT])
        angel_ += 120.0f * settings.DELTA_T / 1000.0f;
    if (keys[KEY_RIGHT])
        angel_ -= 120.0f * settings.DELTA_T / 1000.0f;
    move_[MOVE_FOREWARD] = keys[KEY_UP];

    if (isFlying)
    {
        vx += accel * cos(angel_ * M_PI /180) * settings.DELTA_T/1000.0f;
        vy += accel * sin(angel_* M_PI /180) * settings.DELTA_T/1000.0f;

        if (vx < -velLimit)
            vx = velLimit;
        else if(vx > velLimit)
            vx = velLimit;
    
        if (vy < -velLimit)
            vy = velLimit;
        else if(vy > velLimit)
            vy = velLimit;
    }
    else{

        vx *= 0.6;
        vy *= 0.6;
    }
    
    
    x += vx;
    y += vy;
    
}

void Ship::draw(Renderer &p, int wChange, int hChange)
{
    p.drawShip(x + wChange/2, y + hChange/2, angel_);
}
