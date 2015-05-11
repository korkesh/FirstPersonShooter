//
//  particleNewton.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-13.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include "particleNewton.h"

#include <GLUT/GLUT.h>
#include <glm/glm.hpp>
#include <vector>

ParticleNewton particleSystem[MAX_PARTICLES];

float speed;
float step;

bool gravity = true;
float coef;

Vector3D rotateNewton(Vector3D v, Vector3D axis, float degrees) {
	axis.normalize();
	float radians = degrees * M_PI / 180;
	float s = sin(radians);
	float c = cos(radians);
	return c * v + (1 - c) * axis.dot(v) * axis + s * v.cross(axis);
}


void NewtonEngine(int x, int y, int z)
{
    speed = 1.0f;
    step = 0.0f;
    
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particleSystem[i].mass = 1.0f;
        
        // source for circular particles: http://3dgep.com/simulating-particle-effects-using-opengl/
        float inclination = glm::radians((float)rand() / 360);
        float azimuth = glm::radians((float)rand() / 360);
        
        float sInclination = sinf( inclination );
        
        float X = sInclination * cosf( azimuth );
        float Y = sInclination * sinf( azimuth );
        float Z = cosf( inclination );

        particleSystem[i].posistion = 0.5f * Vector3D(X, Y, Z) + Vector3D(x, y, z);
        particleSystem[i].posistionOriginal = particleSystem[i].posistion;
        
        for (int j = 0; j < 2; j++) {
            particleSystem[i].color[j] = (float)rand() / ((float)RAND_MAX + 1);
            particleSystem[i].velocity[j] = speed * 2.0 * ((float) rand() / RAND_MAX) - 1.0;
        }
        
        particleSystem[i].velocityOriginal = particleSystem[i].velocity;

        particleSystem[i].color[0] = 1.0f;
        
        particleSystem[i].lifespan = (float)rand() / ((float)RAND_MAX + 1);
        particleSystem[i].last_time = glutGet(GLUT_ELAPSED_TIME);
    }
}

ParticleNewton initializeParticle()
{
    ParticleNewton p;
    p.mass = 1.0f;
    p.posistion = p.posistionOriginal;
    p.velocity = p.velocityOriginal;
    
    for (int j = 0; j < 2; j++) {
        p.color[j] = (float)rand() / ((float)RAND_MAX + 1);
    }
    
    p.color[0] = 1.0f;
    p.lifespan = (float)rand() / ((float)RAND_MAX + 1);
    p.last_time = glutGet(GLUT_ELAPSED_TIME);

    return p;
    
}

void drawParticlesNewton()
{
    std::vector<ParticleNewton*> particleList;
    for(int i = 0; i < MAX_PARTICLES; i++) {
        particleList.push_back(particleSystem + i);
    }
    glBegin(GL_QUADS);
    for(unsigned int i = 0; i < particleList.size(); i++) {
        ParticleNewton* particle = particleList[i];
        if (particle->lifespan < 0.01) {
            continue;
        }
        glColor4f(particle->color[0], particle->color[1], particle->color[2], particle->lifespan);
        float size = 0.03 / 3;
        
//        Vector3D pos = rotateNewton(particle->posistion, Vector3D(0, 1, 0), -30);
        Vector3D pos = particle->posistion;
        
        glVertex3f(pos[0] - size, pos[1] - size, pos[2]);
        glVertex3f(pos[0] - size, pos[1] + size, pos[2]);
        glVertex3f(pos[0] + size, pos[1] + size, pos[2]);
        glVertex3f(pos[0] + size, pos[1] - size, pos[2]);
    }
    glEnd();

}

float forces(int i, int j)
{
    if (!gravity)
    {
        return 0.0f;
    }
    else if (j == 1)
    {
        return -1.0f;
    }
    else
    {
        return 0.0f;
    }
}

void collision(int n)
{
    for (int i = 0; i < 3; i++) {
        if (particleSystem[n].posistion[1] <= 0.1) {
            particleSystem[n].velocity[1] = -coef * particleSystem[n].velocity[i];
            particleSystem[n].posistion[1] = 0.1 - coef * (particleSystem[n].posistion[i] + 1.0);
        }
    }
}

void idle(double t)
{
    float dt;
    float present_time = t;
    
    while (t > 0) {
        if (step < t) {
            t -= step;
            
            for (int i = 0; i < MAX_PARTICLES; i++) {
                dt = 0.01;
                for (int j = 0; j < 2; j++) {
                    particleSystem[i].posistion[j] += dt * particleSystem[i].velocity[j];
                    particleSystem[i].velocity[j] += dt * forces(i,j) / particleSystem[i].mass;
                }
                
                collision(i);
                
//                float cm[3];
//                for (int k = 0; k < 3; k++) {
//                    cm[k] = 0;
//                    for (int i = 0; i < MAX_PARTICLES; i++) {
//                        cm[k] += particleSystem[i].posistion[k];
//                    }
//                    cm[k] = cm[k] /  MAX_PARTICLES;
//                }
//                
//                for (int j = 0; j < 3; j++) {
//                    particleSystem[i].velocity[j] += cm[j];
//                }
                
                particleSystem[i].lifespan -= 0.01;
                if (particleSystem[i].lifespan < 0.001)
                {
                    particleSystem[i].lifespan = 0.0f;
                }
                
            }
            
            step = 0.01;
        }
        else {
            step -= t;
            t = 0;
        }
    }
    
    
}


