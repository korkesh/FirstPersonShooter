//
//  skybox.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-13.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "skybox.h"

void drawSkybox(float xpos, float ypos, float zpos) {
	glColor3f(1.0, 1.0, 1.0);
    
	glPushMatrix();
    
	glTranslatef(xpos, ypos, zpos);
    glScalef(30, 30, 30);
    
	float border = 1.005f;
    
	// Top
	glBindTexture(GL_TEXTURE_2D,textureSkybox[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-border, 1.0f, -border);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-border, 1.0f, border);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(border, 1.0f, border);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(border, 1.0f, -border);
    
	glEnd();
    
	// Bottom
	glBindTexture(GL_TEXTURE_2D,textureSkybox[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-border,-1.0f,-border);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-border,-1.0f, border);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( border,-1.0f, border);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( border,-1.0f,-border);
    
	glEnd();
    
	// Left
	glBindTexture(GL_TEXTURE_2D,textureSkybox[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -border, border);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  border, border);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f,  border,-border);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -border,-border);
    
	glEnd();
    
	// Right
	glBindTexture(GL_TEXTURE_2D,textureSkybox[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -border, border);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f,  border, border);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f,  border, -border);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -border, -border);
    
	glEnd();
    
	// Behind
	glBindTexture(GL_TEXTURE_2D, textureSkybox[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( border, -border, 1.0f);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( border,  border, 1.0f);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-border,  border, 1.0f);
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-border, -border, 1.0f);
    
	glEnd();
    
	// Front
	glBindTexture(GL_TEXTURE_2D,textureSkybox[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( border, -border, -1.0f);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( border,  border, -1.0f);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-border,  border, -1.0f);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-border, -border, -1.0f);
    
	glEnd();
    
	// Load Saved Matrix
	glPopMatrix();
    
}
