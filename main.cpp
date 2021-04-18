#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#if _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "settings.h"
#include "keys.h"
#include "renderer.h"
#include "arena.h"
#include "game.h"
#include "bullet.h"
#include <cmath>
#include <iostream>

#define KEY_W 'w'
#define KEY_D 'd'
#define KEY_A 'a'
#define KEY_SPACE ' '
#define KEY_ESC 27

Settings settings;
Keys keys;
Renderer r;
Game g;

Ship ship;
Arena arena;
Asteroid asteroid;
Bullet bullet;
std::vector<Asteroid> asteroids;
std::vector<Bullet> bullets;

void shootBullet(float dt);

// Method to run on reshape of screen size
void on_reshape(int w, int h){

    glViewport(0, 0, w, h);  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  

    int viewport_aspect = w / h;
    int arena_aspect = w / h;

    if (viewport_aspect >= arena_aspect)
    {
        glOrtho(0, w * viewport_aspect / arena_aspect, 0, h * viewport_aspect / arena_aspect, -1, 1);
        settings.WIDTH = w * viewport_aspect / arena_aspect;  
        settings.HEIGHT = h * viewport_aspect / arena_aspect;
        settings.hypotenuse = sqrt((settings.WIDTH * settings.WIDTH) + (settings.HEIGHT * settings.HEIGHT));
    }
    else{
        glOrtho(0, w * arena_aspect / viewport_aspect, 0, h * arena_aspect / viewport_aspect, -1, 1);
        settings.WIDTH = w * arena_aspect / viewport_aspect;  
        settings.HEIGHT = h * arena_aspect / viewport_aspect;
        settings.hypotenuse = sqrt((settings.WIDTH * settings.WIDTH) + (settings.HEIGHT * settings.HEIGHT));
    }   
}

// Event to check for when space is pressed
void on_Key_Press(unsigned char key, int, int)
{
    switch(key)
    {
    case KEY_W:
        ship.isFlying = true;
        break;
    case KEY_D:
        keys.set(KEY_RIGHT);
        break;
    case KEY_A:
        keys.set(KEY_LEFT);
        break;
    case KEY_SPACE:
        keys.set(KEY_FIRE);
        break;
    }
}

// Event to check for when space is released
void on_Key_Release(unsigned char key, int, int)
{
    switch(key)
    {
    case KEY_W:
        ship.isFlying = false;
        break;
    case KEY_D:
        keys.reset(KEY_RIGHT);
        break;
    case KEY_A:
        keys.reset(KEY_LEFT);
        break;
    case KEY_SPACE:
        keys.reset(KEY_FIRE);
        break;
    case KEY_ESC:
        exit(EXIT_SUCCESS);
    }
}

//Method that ticks between every frame
void on_Idle()
{   
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float timeChange = time - settings.oldTime;
    settings.countWave -= timeChange;

    Vector v {0, 0};

    ship.tick(keys, settings, v);

    if ((ship.x < 0) | (ship.x > settings.WIDTH) | (ship.y < 0) | (ship.y > settings.HEIGHT))
    {
        ship.x = 150;
        ship.y = 150;
        ship.vx = 0;
        ship.vy = 0;
        ship.angel_ = 90;
        asteroids.clear();
        settings.oldTime = 0.0f;
        settings.countWave = 5.0f;
        settings.spawnRate = 1;
    }

    if (settings.countWave <= 0.0f)
    {
        for (int i = 0; i < settings.spawnRate; i++)
        {
            asteroids.push_back(g.spawnAsteroids(settings, ship));
        }
        settings.spawnRate++;
        settings.countWave = 5.0f;
    }

    for (Asteroid &a : asteroids)
    {
        g.launchAsteroid(a, settings);
    }

    for (Asteroid &a : asteroids)
    {
        if (g.checkCollision(ship, a))
        {
            ship.x = 150;
            ship.y = 150;
            ship.angel_ = 90;
            asteroids.clear();
            settings.oldTime = 0.0f;
            settings.countWave = 5.0f;
            settings.spawnRate = 1;
            break;
        }
    }

    g.checkAsteroidCollision(asteroids);
    shootBullet(timeChange);
    g.updateBulletMovement(bullets, settings);
    g.bulletAsteroidCollision(bullets, asteroids, settings);
    
    
    settings.oldTime += timeChange;
    glutPostRedisplay();
}


// Display method to handle all drawing to screen
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    ship.draw(r, settings.wChange, settings.hChange);
    arena.draw(r, settings, ship);
    asteroid.draw(r, asteroids, ship);
    
    for (Bullet b: bullets)
        bullet.draw(r, b);    

    glutSwapBuffers();
}

void OnMouseClick(int button, int state, int x, int y){
    if (button == 0 && state == 0)
    {
        ship.isFiring = true;
    }

    if (button == 0 && state == 1)
    {
        ship.isFiring = false;
    }
    
}

void shootBullet(float dt){
    if (ship.isFiring)
    {
        ship.nextBullet -= dt;
        
        if (ship.nextBullet <= 0)
        {
            Bullet b;

            b.x = ship.x;
            b.y = ship.y;

            b.vx *= cos(ship.angel_ * M_PI / 180);
            b.vy *= sin(ship.angel_ * M_PI / 180);
            b.isInArena = true;
            bullets.push_back(b);
        
            ship.nextBullet = ship.rateOfFire;

        }
        
    }
    
}


// Main Method to Initialize the game and loop for events
int main(int argc, char **argv)
{
    srand(time(0));
    //Initialize Game and set to full screen
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Asteroids");
    glutFullScreen();

    //Draw the Game to the Scene
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(display);

    // Check for Key Presses in Game
    glutKeyboardFunc(on_Key_Press);
    glutKeyboardUpFunc(on_Key_Release);
    glutMouseFunc(OnMouseClick);

    glutIdleFunc(on_Idle);
    
    glutMainLoop();
}
