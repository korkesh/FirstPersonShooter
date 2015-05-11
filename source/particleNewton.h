//
//  particleNewton.h
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-13.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#ifndef __openGLTutorial__particleNewton__
#define __openGLTutorial__particleNewton__

#include "algebra.hpp"

#define MAX_PARTICLES (1000)

struct ParticleNewton
{
    Vector3D posistion;
    Vector3D posistionOriginal;
    Vector3D velocity;
    Vector3D velocityOriginal;
    Vector3D color;
    
    float mass;
    float lifespan;
    float last_time;
    
};

//class NewtonEngine {
extern ParticleNewton particleSystem[MAX_PARTICLES];

    void collision(int n);
    float forces(int i, int j);
    Vector3D rotate(Vector3D v, Vector3D axis, float degrees);
    
//public:
    void NewtonEngine(int x = 0, int y = 0, int z = 0);
    ParticleNewton initializeParticle(int x = 0, int y = 0, int z = 0);

    void drawParticlesNewton();
    void idle(double t);

//};

#endif /* defined(__openGLTutorial__particleNewton__) */
