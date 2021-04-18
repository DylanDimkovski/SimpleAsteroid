#include "arena.h"

Arena::Arena(){}

void Arena::draw(Renderer &p, Settings s, Ship ship)
{
    if (s.wChange >= (s.WIDTH - s.WIDTH/2) || s.hChange >= (s.HEIGHT - s.HEIGHT/2))
    {
        s.wChange = 0;
        s.hChange = 0;
    }
    
    int newScreenWidth = s.WIDTH - s.wChange;
    int newScreenHeight = s.HEIGHT - s.hChange;

    p.drawArena(newScreenWidth, newScreenHeight, s.wChange, s.hChange, ship);
}