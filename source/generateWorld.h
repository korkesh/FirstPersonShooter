//
//  generateWorld.h
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-12.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#ifndef __openGLTutorial__generateWorld__
#define __openGLTutorial__generateWorld__

#include <iostream>
#include "algebra.hpp"

void SetupWorld();
void drawSceneFromFile(GLuint* textures);
bool checkCollisions(int xpos, int ypos, int zpos);

#endif /* defined(__openGLTutorial__generateWorld__) */
