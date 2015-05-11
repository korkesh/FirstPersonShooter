//
//  target.h
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-15.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#ifndef __openGLTutorial__target__
#define __openGLTutorial__target__

#include <GLUT/GLUT.h>
#include <OpenAL/al.h>
#include "algebra.hpp"
#include "particleNewton.h"

#define NUM_TARGETS (5)

enum TARGET_STATE { DEFAULT = 0, EXPLODING = 1, DEAD = 2 };

struct Target {
    Point3D position;
    TARGET_STATE state;
    
    ALuint soundEffect;
};

extern Target targets[NUM_TARGETS];

void initializeTargets();
void drawTarget();
//void processHits(GLint hits, GLuint buffer[]);

#endif /* defined(__openGLTutorial__target__) */
