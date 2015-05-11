//
//  particle.h
//

#ifndef __openGLTutorial__particle__
#define __openGLTutorial__particle__

#include <iostream>
#include <vector>
#include <GLUT/GLUT.h>
#include "algebra.hpp"

const int NUM_PARTICLES = 1000;

//Represents a single particle.
struct Particle {
	Vector3D pos;
	Vector3D velocity;
	Vector3D color;
	float timeAlive; //The amount of time that this particle has been alive.
	float lifespan;  //The total amount of time that this particle is to live.
};


class ParticleEngine {
public:
    ParticleEngine(GLuint textureId1);
    
    //Advances the particle fountain by the specified amount of time.
    void advance(float dt);
    
    //Draws the particle fountain.
    void draw();
    
private:
    GLuint textureId;
    Particle particles[NUM_PARTICLES];
    //The amount of time until the next call to step().
    float timeUntilNextStep;
    //The color of particles that the fountain is currently shooting.  0
    //indicates red, and when it reaches 1, it starts over at red again.  It
    //always lies between 0 and 1.
    float colorTime;
    //The angle at which the fountain is shooting particles, in radians.
    float angle;
    
    //Returns the current color of particles produced by the fountain.
    Vector3D curColor();
    
    //Returns the average velocity of particles produced by the fountain.
    Vector3D curVelocity();
    
    //Alters p to be a particle newly produced by the fountain.
    void createParticle(Particle* p);
    
    //Advances the particle fountain by STEP_TIME seconds.
    void step();
};


#endif /* defined(__openGLTutorial__particle__) */
