//
//  animation.cpp
//
//  Created by Matthew Correia on 2014-07-16.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include <GLUT/glut.h>

#include "animation.h"
#include "texture.h"

int shoulderAngle = 115;
int elbowAngle = 0;

float bulletPos = 0.8;

int framesE[3] = {0, 45, 60};
float framesB[5] = {0.7, 1.5, 2.0, 2.5, 2.9};

float animationTime = 0.0;
int startFrame = 0;
int endFrame = 3;
int endFrameB = 5;

bool drawBullet = true;

void drawSphere(GLdouble width, GLdouble height, GLdouble depth, int texture) {
    glPushMatrix();
    glScalef(width, height, depth);
    
    if (texture != -1) {
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, textureMenu[texture]);
    }
    GLUquadricObj* quadratic = gluNewQuadric();
    gluQuadricNormals( quadratic, GLU_SMOOTH );
    gluQuadricTexture( quadratic, GL_TRUE );
    
    gluSphere( quadratic, 0.5f, 32, 32 );

    glPopMatrix();
}

void displayArm() {
    
    //Figure out the two frames between which we are interpolating
	int frameIndex1 = (int)(animationTime * (endFrame - startFrame + 1)) + startFrame;
	if (frameIndex1 > endFrame) {
		frameIndex1 = startFrame;
	}
	
	int frameIndex2;
	if (frameIndex1 < endFrame) {
		frameIndex2 = frameIndex1 + 1;
	}
	else {
		frameIndex2 = startFrame;
	}
	
	int angle1 = framesE[frameIndex1];
	int angle2 = framesE[frameIndex2];
    
    int frameIndex1B = (int)(animationTime * (endFrameB - startFrame + 1)) + startFrame;
	if (frameIndex1B > endFrameB) {
		frameIndex1B = startFrame;
	}
	
	int frameIndex2B;
	if (frameIndex1B < endFrameB) {
		frameIndex2B = frameIndex1B + 1;
	}
	else {
		frameIndex2B = startFrame;
	}
    
    float pos1B = framesB[frameIndex1B];
    float pos2B = framesB[frameIndex2B];


	//Figure out the fraction that we are between the two frames
	float inbetween = (animationTime - (float)(frameIndex1 - startFrame) / (float)(endFrame - startFrame + 1)) * (endFrame - startFrame + 1);
    elbowAngle = angle1 * (1 - inbetween) + angle2 * inbetween;
    
    float inbetweenB = (animationTime - (float)(frameIndex1B - startFrame) / (float)(endFrameB - startFrame + 1)) * (endFrameB - startFrame + 1);
    bulletPos = pos1B * (1 - inbetweenB) + pos2B * inbetweenB;
    if (pos2B < pos1B) {
        drawBullet = false;
        bulletPos = framesB[endFrameB];
    }
    else if (bulletPos < framesB[startFrame]) {
        bulletPos = framesB[startFrame];
        drawBullet = false;
    } else {
        drawBullet = true;
    }
    
    
    // Torso
    glPushMatrix();
    glTranslatef(-0.65, 0.45, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawSphere(0.9, 0.5, 0.2, 2);
    glPopMatrix();
    
    // Arm
    glPushMatrix();
    glTranslatef(-0.12, 0, 0);
    
    glPushMatrix();
    glTranslatef(-0.15, 0.45, 0.0);
    glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
    drawSphere(0.75, 0.2, 0.2, 2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.15, 0.0);
    glRotatef(elbowAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.29, 0.0, 0.0);
    drawSphere(0.6, 0.2, 0.2, 2);
    
    
    // Hand
    glPushMatrix();
    glTranslatef(0.39f, 0.0, 0.0);
    drawSphere(0.2, 0.2, 0.2, 2);
    
    // Gun
    glPushMatrix();
    glTranslatef(0.0f, 0.15, 0);
    glRotatef(90, 0, 0, 1);
    drawSphere(0.25, 0.075, 0.075, 1);
    
    glTranslatef(0.05, -0.07, 0);
    drawSphere(0.1, 0.3, 0.1, 3);

    glTranslatef(0, -0.05, 0);
    drawSphere(0.15, 0.05, 0.15, 4);

    glTranslatef(0, -0.05, 0);
    drawSphere(0.1, 0.05, 0.1, 4);

    glTranslatef(0, -0.05, 0);
    drawSphere(0.05, 0.05, 0.05, 4);
    
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    if (drawBullet) {
        // Bullet
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glDisable(GL_TEXTURE_2D);
        glTranslatef(bulletPos, 0.35, 0);
        glRotatef(90, 0, 1, 0);
        drawSphere(0.05, 0.05, 0.2, -1);
        glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
    }
}

void updateArm(float time)
{
    if (time < 0) {
		return;
	}
	
	animationTime += time;
	if (animationTime < 1000000000) {
		animationTime -= (int)animationTime;
	}
	else {
		animationTime = 0;
	}

    
}

