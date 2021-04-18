#include "game.h"
#include <iostream>
Game::Game(){}


Asteroid Game::spawnAsteroids(Settings s, Ship ship){

    Asteroid a;
    float xSide, ySide;
    xSide = rand() % (s.hypotenuse - s.WIDTH);
    ySide = rand() % (s.hypotenuse - s.HEIGHT);

    a.x = rand() % 2 == 0 ? xSide + s.WIDTH : -xSide;
    a.y = rand() % 2 == 0 ? ySide + s.HEIGHT : -ySide;
    a.size = rand() % (100 - 50) + 50;
    a.angle = a.angle * M_PI / 180;

    int randValue = rand() % (6 - 3) + 3;

    for (int i = 0; i < a.pointSize; i++)
    {
        a.pointArray.push_back((rand() % (100 - 60) + 60) / 100);
    }
    

    a.vx = -cos(acos((a.x - ship.x) / sqrt(pow(a.y - ship.y, 2) + pow(a.x - ship.x, 2)))) * randValue;
    a.vy = -sin(asin((a.y - ship.y) / sqrt(pow(a.y - ship.y, 2) + pow(a.x - ship.x, 2)))) * randValue;
    a.vr *= rand() % 2 == 0 ? -1 : 1;
    
    return a;
}

void Game::launchAsteroid(Asteroid &a, Settings s){
    a.x += a.vx;
    a.y += a.vy;
    a.angle += a.vr;

    bool top = a.y + a.size > s.HEIGHT;
    bool bot = a.y - a.size < 0;
    bool left = a.x - a.size < 0;
    bool right = a.x + a.size > s.WIDTH;

    if (a.insideArena)
    {
        if (top || bot)
        {
            a.vy *= -1;
        }

        if (left || right)
        {
            a.vx *= -1;
        }        
    }
    else if(!top && !bot && !left && !right){
        a.insideArena = true;
    }
}

bool Game::checkCollision(Ship ship, Asteroid &asteroid){

    int hypotenuse;
    int a,b;
    asteroid.radius = asteroid.size;
    ship.radius = 5;

    a = asteroid.x - ship.x;
    b = asteroid.y - ship.y;

    hypotenuse = sqrt(pow(a,2) + pow(b,2));
    
    return abs(hypotenuse) < (asteroid.radius + ship.radius);
}

bool Game::checkAsteroidCollision(std::vector<Asteroid> &asteroids){
    
    for (int i = 0; i < asteroids.size(); i++)
    {
        for (int j = i + 1; j < asteroids.size(); j++)
        {
            Asteroid &a = asteroids.at(i);
            Asteroid &b = asteroids.at(j);

            if (circleCollision(a.x, b.x, a.y, b.y, a.radius, b.radius))
            {
                float axOld = a.vx;
                float bxOld = b.vx;
                float ayOld = a.vy;
                float byOld = b.vy;

                a.vx = bxOld;
                a.vy = byOld;
                b.vx = axOld;
                b.vy = ayOld;
            }
        }
    }
}

bool Game::circleCollision(float x1, float x2, float y1, float y2, float r1, float r2){
    
    int hypotenuse;
    int a,b;


    a = x1 - x2;
    b = y1 - y2;

    hypotenuse = sqrt(pow(a,2) + pow(b,2));
    
    return abs(hypotenuse) < (r1 + r2);
}

void Game::updateBulletMovement(std::vector<Bullet> &bullet, Settings settings){

    for (int i = 0; i < bullet.size(); i++)
    {
        Bullet &b = bullet.at(i);

        b.x += b.vx;
        b.y += b.vy;

        if (b.x > settings.WIDTH || b.x < 0)
        {
            bullet.erase(bullet.begin() + i);
        }
        else if (b.y > settings.HEIGHT || b.y < 0)
        {
            bullet.erase(bullet.begin() + i);
        }
    }
    
}

void Game::bulletAsteroidCollision(std::vector<Bullet> &bullets, std::vector<Asteroid> &asteroids, Settings settings){
    
    for (int i = 0; i < bullets.size(); i++)
    {
        Bullet &a = bullets.at(i);
        for (int j = 0; j < asteroids.size(); j++)
        {
            Asteroid &b = asteroids.at(j);

            if (circleCollision(a.x, b.x, a.y, b.y, 0, b.size))
            {
                b.health -= a.damage;

                if (b.health <= 0)
                {
                    settings.playerPoints += b.points;
                    asteroids.erase(asteroids.begin() + j);
                    bullets.erase(bullets.begin() + i);
                }
                
            }
        }
    }
}