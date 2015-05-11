//
//  collision.h
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-13.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#ifndef __openGLTutorial__collision__
#define __openGLTutorial__collision__

#include <iostream>

enum OBJECT {RED_BALL = 0, BLUE_BALL, CAMERA};

void initializeBalls();
void initializeWalls();
void stepBalls(float time, float timeUntilUpdate, int xpos, int ypos, int zpos);
void drawBalls();
void drawWalls();

bool testWallCollision(OBJECT object, int xpos = 0, int ypos = 0, int zpos = 0);
bool testCameraCollision(int xpos, int ypos, int zpos);

#endif /* defined(__openGLTutorial__collision__) */
