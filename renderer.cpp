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

#include <cmath>
#include <bitset>
#include "renderer.h"

void Renderer::drawAsteroid(float x, float y, float angle, float size)
{
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    glColor3f(0.5, 0.5, 0.5);   

    //int randValue = rand() % (7-5) + 5;

    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; ++i)
    {
        float radian = ((360 / 5) * i) * (M_PI / 180);
        float x = cosf(radian) * size;
        float y = sinf(radian) * size;
        glVertex2f(x, y);
    }
    glEnd();        
    

    glPopMatrix();

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, 0);

    glPopMatrix();
}

void Renderer::drawShip(float x, float y, float angle)
{
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(angle - 90, 0, 0, 1);
    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 20);
    glVertex2f(10, -10);
    glVertex2f(0, 0);
    glVertex2f(-10, -10);
    glEnd();
    
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(0, 20);
    glVertex2f(0, 0);
    glEnd();

    glColor3f(1, 0, 0);
    if (true)
    {
        glLineWidth(5.0f);
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0, -30);
        glEnd();
        glLineWidth(1.0f);
    }
    glPopMatrix();
}

void Renderer::drawBullet(float x, float y)
{
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x, y, 0);
    glPointSize(3);

    glColor3f(1, 0, 1);

    glBegin(GL_POINTS);
    glVertex2f(0, 0);
    glEnd();

    glPointSize(1);

    glPopMatrix();
}

void Renderer::drawArena(int width, int height, int wChange, int hChange, Ship s)
{
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();  

    //Bottom Left Corner to Bottom Right
    if (s.y <= ((height - height) + hChange/2) + 100)
    {
        glColor3f(1,0,0);
    }
    else{glColor3f(1,1,1);}
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glVertex2f((width - width) + wChange/2, (height - height) + hChange/2);
    glVertex2f(width + wChange/2, (height - height) + hChange/2);
    glEnd();
    glLineWidth(1.0f);

    //Bottom Right Corner to Top Right
    if (s.x >= (width + wChange/2) - 100)
    {
        glColor3f(1,0,0);
    }
    else{glColor3f(1,1,1);}
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glVertex2f(width + wChange/2, (height - height) + hChange/2);
    glVertex2f(width + wChange/2, height + hChange/2);
    glEnd();
    glLineWidth(1.0f);

    //Top Right Corner to Top Left
    if (s.y >= (height + hChange/2) - 100)
    {
        glColor3f(1,0,0);
    }
    else{glColor3f(1,1,1);}
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glVertex2f((width - width) + wChange/2, height + hChange/2);
    glVertex2f(width + wChange/2, height + hChange/2);
    glEnd();
    glLineWidth(1.0f);

    //Top Left Corner to Bottom Left
    if (s.x <= ((width - width) + wChange/2) + 100)
    {
        glColor3f(1,0,0);
    }
    else{glColor3f(1,1,1);}
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glVertex2f((width - width) + wChange/2, height + hChange/2);
    glVertex2f((width - width) + wChange/2, (height - height) + hChange/2);
    glEnd();
    glLineWidth(1.0f);

    glPopMatrix();
}


void Renderer::drawBullet(float x, float y, float size){

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x, y, 0);
    glColor3f(1,1,1);
    glPointSize(size); 
    glBegin(GL_POINTS);
    glVertex2f(0, 0);
    glEnd();


    glPopMatrix();

    glPointSize(1.0f);
}