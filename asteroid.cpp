#include "asteroid.h"
#include <cmath>

Asteroid::Asteroid(): angle(rand() % 3140 / 1000.0f) {}

void Asteroid::draw(Renderer &p, std::vector<Asteroid> &asteroids, Ship s)
{    
    for(Asteroid a : asteroids){
        p.drawAsteroid(a.x, a.y, a.angle, a.size);
    }
}

