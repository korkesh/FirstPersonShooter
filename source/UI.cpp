//
//  UI.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-15.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <sstream>

#include "UI.h"
#include "texture.h"
#include "animation.h"

#define WIDTH (1024)
#define HEIGHT (768)

int score = -2;
int health = 100;

void drawMenu()
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    glLoadName(1);

    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(1.0f, 1.0f, 0.0f);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureMenu[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.0f);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    
    displayArm();
    
    glPopMatrix();
    
}

void drawUI() {
    glDisable(GL_LIGHTING);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    if (score == 5) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, HEIGHT);
        glVertex2f(WIDTH, HEIGHT);
        glVertex2f(WIDTH, 0);
        glEnd();
        
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2i(250, 600);
        
        std::stringstream ss;
        ss << "Congratulations! You have stopped the evil alien orb things";
        
        std::string s = ss.str();
        void * font = GLUT_BITMAP_TIMES_ROMAN_24;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        
        glRasterPos2i(250, 550);
        std::stringstream ss2;
        ss2 << "from destorying this little bit of land in the middle of nowhere!";
        s = ss2.str();
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        
        glRasterPos2i(250, 500);
        std::stringstream ss3;
        ss3 << "To reward you for you bravey I present you a cookie.";
        s = ss3.str();
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }

        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureCookie);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(WIDTH/2 - 100, HEIGHT/2 - 200, 0.0f);
        
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(WIDTH/2 - 100, HEIGHT/2, 0.0f);
        
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(WIDTH/2 + 100, HEIGHT/2, 0.0f);
        
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(WIDTH/2 + 100, HEIGHT/2 - 200, 0.0f);
        glEnd();
        
    }
    else if (score <= -1)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, HEIGHT);
        glVertex2f(WIDTH, HEIGHT);
        glVertex2f(WIDTH, 0);
        glEnd();
        
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2i(300, 600);
        
        std::stringstream ss;
        ss << "Welcome to my CS488 OpenGL Project!";
        
        std::string s = ss.str();
        void * font = GLUT_BITMAP_TIMES_ROMAN_24;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        
        glRasterPos2i(260, 550);
        std::stringstream ss2;
        ss2 << "Your mission is to find the 5 alien orbs scattered";
        s = ss2.str();
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        
        glRasterPos2i(260, 500);
        std::stringstream ss3;
        ss3 << "around the world and destroy them. Best of Luck!";
        s = ss3.str();
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }

    }
    else
    {
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2i(10, 720);
        
        std::stringstream ss;
        ss << "HEALTH: 100          SCORE: " << score;
        
        std::string s = ss.str();
        void * font = GLUT_BITMAP_TIMES_ROMAN_24;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        
        // CrossHair
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(WIDTH / 2 - 2, HEIGHT / 2 - 30);
        glVertex2f(WIDTH / 2 - 2, HEIGHT / 2 - 10);
        glVertex2f(WIDTH / 2 + 2, HEIGHT / 2 - 10);
        glVertex2f(WIDTH / 2 + 2, HEIGHT / 2 - 30);
        glEnd();
        
        glBegin(GL_QUADS);
        glVertex2f(WIDTH / 2 - 2, HEIGHT / 2 + 30);
        glVertex2f(WIDTH / 2 - 2, HEIGHT / 2 + 10);
        glVertex2f(WIDTH / 2 + 2, HEIGHT / 2 + 10);
        glVertex2f(WIDTH / 2 + 2, HEIGHT / 2 + 30);
        glEnd();
        
        glBegin(GL_QUADS);
        glVertex2f(WIDTH / 2 - 30, HEIGHT / 2 - 2);
        glVertex2f(WIDTH / 2 - 30, HEIGHT / 2 + 2);
        glVertex2f(WIDTH / 2 - 10, HEIGHT / 2 + 2);
        glVertex2f(WIDTH / 2 - 10, HEIGHT / 2 - 2);
        glEnd();
        
        glBegin(GL_QUADS);
        glVertex2f(WIDTH / 2 + 30, HEIGHT / 2 - 2);
        glVertex2f(WIDTH / 2 + 30, HEIGHT / 2 + 2);
        glVertex2f(WIDTH / 2 + 10, HEIGHT / 2 + 2);
        glVertex2f(WIDTH / 2 + 10, HEIGHT / 2 - 2);
        glEnd();
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void fireGun()
{    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureGun);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(WIDTH/2 + 100, HEIGHT/2 + 100, 0.0f);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(WIDTH/2 + 100, HEIGHT/2 + 300, 0.0f);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(WIDTH/2 + 400, HEIGHT/2 + 300, 0.0f);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(WIDTH/2 + 400, HEIGHT/2 + 100, 0.0f);
    glEnd();
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

}
