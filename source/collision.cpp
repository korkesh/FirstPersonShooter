//
//  collision.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-13.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//
#include <GLUT/GLUT.h>

#include "collision.h"
#include "algebra.hpp"
#include "texture.h"

const float TIME_BETWEEN_UPDATES = 0.01f;

struct Ball {
    Vector3D position;
    Vector3D velocity;
    float radius;
    Vector3D color;
} ballRed, ballBlue;

struct Wall {
    Vector3D normal;
} wallLeft, wallRight, wallFront, wallBack, wallTop, wallBottom;

void initializeBalls()
{
    ballRed.position = Vector3D(0.0, 0.5, 0.0);
    ballRed.velocity = Vector3D(0.0, 3.0, 0.0);
    ballRed.radius = 0.1f;
    ballRed.color = Vector3D(1.0, 0.0, 0.0);
    
    ballBlue.position = Vector3D(0.5, 0.5, 0.0);
    ballBlue.velocity = Vector3D(3.0, 0.0, 0.0);
    ballBlue.radius = 0.1f;
    ballBlue.color = Vector3D(0.0, 0.0, 1.0);
}

void initializeWalls()
{
    wallLeft.normal = Vector3D(-1, 0, 0);
    wallRight.normal = Vector3D(1, 0, 0);
    wallFront.normal = Vector3D(0, 0, -1);
    wallBack.normal = Vector3D(0, 0, 1);
    wallTop.normal = Vector3D(0, -1, 0);
    wallBottom.normal = Vector3D(0, 1, 0);
}

void drawWalls()
{
    glBindTexture(GL_TEXTURE_2D, texturesEnvironment[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
    
    // Top
    glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 0.05, -0.5);
    
    glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 0.05, 0.5);
    
    glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5,  0.05, 0.5);
    
    glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5,  0.05, -0.5);
	
    // Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 1.05, -0.5);
    
    glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5,  1.05, -0.5);
    
    glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5,  1.05,  0.5);
    
    glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 1.05,  0.5);
    
    // Left
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 0.05, -0.5);
    
    glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0.05,  0.5);
    
    glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, 1.05,  0.5);
    
    glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 1.05, -0.5);
    
    // Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, 0.05, -0.5);
    
    glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, 0.05,  0.5);
    
    glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 1.05,  0.5);
    
    glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, 1.05, -0.5);
    
    glEnd();
}


void drawBalls()
{
    glPushMatrix();
    glTranslatef(ballRed.position[0], ballRed.position[1], ballRed.position[2]);
    glColor3f(ballRed.color[0], ballRed.color[1], ballRed.color[2]);
    glutSolidSphere(ballRed.radius, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ballBlue.position[0], ballBlue.position[1], ballBlue.position[2]);
    glColor3f(ballBlue.color[0], ballBlue.color[1], ballBlue.color[2]);
    glutSolidSphere(ballBlue.radius, 24, 24);
    glPopMatrix();
    
}

void moveBalls(float time)
{
    for (int i = 0; i < 3; i++) {
        ballRed.position[i] += ballRed.velocity[i] * time;
        ballBlue.position[i] += ballBlue.velocity[i] * time;
    }
}

bool testBallCollision()
{
    bool collide = false;
    
    // Test to see if the balls are touching
    float radi = ballRed.radius + ballBlue.radius;
    Vector3D ballRay = ballRed.position - ballBlue.position;
    
    if (ballRay.dot(ballRay) < radi * radi) {
        Vector3D netVelocity = ballRed.velocity - ballBlue.velocity;
        Vector3D displacement = ballRed.position - ballBlue.position;
        if (netVelocity.dot(displacement) < 0) {
            collide = true;
        }
    }
    
    return collide;
    
}

bool testCameraCollision(int xpos, int ypos, int zpos)
{
    bool collide = false;
    float cameraRadius = 1.0f;
    Vector3D cameraPosition = Vector3D(xpos, ypos, zpos);
    
    float radi = ballRed.radius + cameraRadius;
    Vector3D ballRay = ballRed.position - cameraPosition;
    
    if (ballRay.dot(ballRay) < radi * radi) {
            collide = true;
    }
    
    radi = ballBlue.radius + cameraRadius;
    ballRay = ballBlue.position - cameraPosition;

    if (ballRay.dot(ballRay) < radi * radi) {
        collide = true;
    }

    
    return collide;
    
}

bool testWallCollision(OBJECT object, int xpos, int ypos, int zpos) {
    bool collide = false;
    Vector3D normal;
    
    switch (object) {
        case RED_BALL:
        {
            
            if (ballRed.position[1] < 0) {
                //
            }
            // Left
            normal = wallLeft.normal;
            if (ballRed.position.dot(normal) + ballRed.radius > (1.0 / 2) && ballRed.velocity.dot(normal) > 0) {
                ballRed.velocity = ballRed.velocity - 2 * ballRed.velocity.dot(normal) * normal;
                collide = true;
            }
            
            // Right
            normal = wallRight.normal;
            if (ballRed.position.dot(normal) + ballRed.radius > (1.0 / 2) && ballRed.velocity.dot(normal) > 0) {
                ballRed.velocity = ballRed.velocity - 2 * ballRed.velocity.dot(normal) * normal;
                collide = true;
            }
            
            normal = wallFront.normal;
            if (ballRed.position.dot(normal) + ballRed.radius > (2.0 / 2) && ballRed.velocity.dot(normal) > 0) {
                ballRed.velocity = ballRed.velocity - 2 * ballRed.velocity.dot(normal) * normal;
                collide = true;
            }
            
            normal = wallBack.normal;
            if (ballRed.position.dot(normal) + ballRed.radius > (2.0 / 2) && ballRed.velocity.dot(normal) > 0) {
                ballRed.velocity = ballRed.velocity - 2 * ballRed.velocity.dot(normal) * normal;
                collide = true;
            }
            
            normal = wallTop.normal;
            if (ballRed.position.dot(normal) + ballRed.radius > (2.0 / 2) && ballRed.velocity.dot(normal) > 0) {
                ballRed.velocity = ballRed.velocity - 2 * ballRed.velocity.dot(normal) * normal;
                collide = true;
            }

            normal = wallBottom.normal;
            if ((ballRed.position.dot(normal) < 0.2) || (ballRed.position.dot(normal) + ballRed.radius > 2.0 / 2 && ballRed.velocity.dot(normal) > 0)) {
                ballRed.velocity = ballRed.velocity - 2 * ballRed.velocity.dot(normal) * normal;
                collide = true;
            }
            
            break;
        }
        case BLUE_BALL:
        {
            // Left
            normal = wallLeft.normal;
            if (ballBlue.position.dot(normal) + ballBlue.radius > 1.0 / 2 && ballBlue.velocity.dot(normal) > 0) {
                ballBlue.velocity = ballBlue.velocity - 2 * ballBlue.velocity.dot(normal) * normal;
                collide = true;
            }
            
            // Right
            normal = wallRight.normal;
            if (ballBlue.position.dot(normal) + ballBlue.radius > 1.0 / 2 && ballBlue.velocity.dot(normal) > 0) {
                ballBlue.velocity = ballBlue.velocity - 2 * ballBlue.velocity.dot(normal) * normal;
                collide = true;
            }
            
            normal = wallFront.normal;
            if (ballBlue.position.dot(normal) + ballBlue.radius > 2.0 / 2 && ballBlue.velocity.dot(normal) > 0) {
                ballBlue.velocity = ballBlue.velocity - 2 * ballBlue.velocity.dot(normal) * normal;
                collide = true;
            }
            
            normal = wallBack.normal;
            if (ballBlue.position.dot(normal) + ballBlue.radius > 2.0 / 2 && ballBlue.velocity.dot(normal) > 0) {
                ballBlue.velocity = ballBlue.velocity - 2 * ballBlue.velocity.dot(normal) * normal;
                collide = true;
            }
            
            normal = wallTop.normal;
            if (ballBlue.position.dot(normal) + ballBlue.radius > 2.0 / 2 && ballBlue.velocity.dot(normal) > 0) {
                ballBlue.velocity = ballBlue.velocity - 2 * ballBlue.velocity.dot(normal) * normal;
                collide = true;
            }
        
            normal = wallBottom.normal;
            if ((ballBlue.position.dot(normal) < 0.2) || (ballBlue.position.dot(normal) + ballBlue.radius > 2.0 / 2 && ballBlue.velocity.dot(normal) > 0)) {
                ballBlue.velocity = ballBlue.velocity - 2 * ballBlue.velocity.dot(normal) * normal;
                collide = true;
            }
            break;

        }
        case CAMERA:
        {
            Vector3D pos = Vector3D(xpos, ypos, zpos);
            // Left
            normal = wallLeft.normal;
            if (pos.dot(normal) + 0.5f > 40.0 / 2) {
                collide = true;
            }
            
            // Right
            normal = wallRight.normal;
            if (pos.dot(normal) + 0.5f > 40.0 / 2) {
                collide = true;
            }
            
            // Front
            normal = wallFront.normal;
            if (pos.dot(normal) + 0.5f > 40.0 / 2) {
                collide = true;
            }

            // Back
            normal = wallBack.normal;
            if (pos.dot(normal) + 0.5f > 40.0 / 2) {
                collide = true;
            }

            break;
            
        }
        default:
            break;
    }
    return collide;
}


void handleBallCollisions(int xpos, int ypos, int zpos)
{
    if (testBallCollision()) {
        Vector3D displacement = (ballRed.position - ballBlue.position);
        displacement.normalize();
        ballRed.velocity = ballRed.velocity - 2 * ballRed.velocity.dot(displacement) * displacement;
        ballBlue.velocity = ballBlue.velocity - 2 * ballBlue.velocity.dot(displacement) * displacement;
    }
    
    if (testWallCollision(RED_BALL)) {
        //sound?
    }
    
    if (testWallCollision(BLUE_BALL)) {
        //sound?
    }
}

void stepBalls(float time, float timeUntilUpdate, int xpos, int ypos, int zpos) {
	while (time > 0) {
		if (timeUntilUpdate <= time) {
			moveBalls(timeUntilUpdate);
            handleBallCollisions(xpos, ypos, zpos);
			time -= timeUntilUpdate;
			timeUntilUpdate = TIME_BETWEEN_UPDATES;
		}
		else {
			moveBalls(time);
			timeUntilUpdate -= time;
			time = 0;
		}
	}
}


