#ifndef GAME
#define GAME

#include "asteroid.h"
#include <vector>
#include "settings.h"
#include "bullet.h"

class Game
{
public:
    Game();
    Asteroid spawnAsteroids(Settings s, Ship ship);
    void launchAsteroid(Asteroid &a, Settings s);
    bool checkCollision(Ship s, Asteroid &a);
    bool checkAsteroidCollision(std::vector<Asteroid> &asteroids);
    bool circleCollision(float x1, float x2, float y1, float y2, float r1, float r2);
    void updateBulletMovement(std::vector<Bullet> &bullet, Settings settings);
    void bulletAsteroidCollision(std::vector<Bullet> &bullets, std::vector<Asteroid> &asteroids, Settings settings);
};


#endif