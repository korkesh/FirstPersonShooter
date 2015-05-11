//
//  particle.cpp
//

#include "particle.h"

const float GRAVITY = 3.0f;
//The interval of time, in seconds, by which the particle engine periodically
//steps.
const float STEP_TIME = 0.01f;
//The length of the sides of the quadrilateral drawn for each particle.
const float PARTICLE_SIZE = 0.05f;

//Returns a random float from 0 to < 1
float randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}

//Rotates the vector by the indicated number of degrees about the specified axis
Vector3D rotate(Vector3D v, Vector3D axis, float degrees) {
	axis.normalize();
	float radians = degrees * M_PI / 180;
	float s = sin(radians);
	float c = cos(radians);
	return c * v + (1 - c) * axis.dot(v) * axis + s * v.cross(axis);
}

//Returns the position of the particle, after rotating the camera
Vector3D adjParticlePos(Vector3D pos) {
	return rotate(pos, Vector3D(1, 0, 0), -30);
}

//Returns whether particle1 is in back of particle2
bool compareParticles(Particle* particle1, Particle* particle2) {
	return adjParticlePos(particle1->pos)[2] <
    adjParticlePos(particle2->pos)[2];
}

//==================
// Public Methods
//==================
ParticleEngine::ParticleEngine(GLuint textureId1) {
    textureId = textureId1;
    timeUntilNextStep = 0;
    colorTime = 0;
    angle = 0;
    for(int i = 0; i < NUM_PARTICLES; i++) {
        createParticle(particles + i);
    }
    for(int i = 0; i < 5 / STEP_TIME; i++) {
        step();
    }
}

//Advances the particle fountain by the specified amount of time.
void ParticleEngine::advance(float dt) {
    while (dt > 0) {
        if (timeUntilNextStep < dt) {
            dt -= timeUntilNextStep;
            step();
            timeUntilNextStep = STEP_TIME;
        }
        else {
            timeUntilNextStep -= dt;
            dt = 0;
        }
    }
}

//Draws the particle fountain.
void ParticleEngine::draw() {
    std::vector<Particle*> ps;
    for(int i = 0; i < NUM_PARTICLES; i++) {
        ps.push_back(particles + i);
    }
    sort(ps.begin(), ps.end(), compareParticles);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBegin(GL_QUADS);
    for(unsigned int i = 0; i < ps.size(); i++) {
        Particle* p = ps[i];
        glColor4f(p->color[0], p->color[1], p->color[2],
                  (1 - p->timeAlive / p->lifespan));
        float size = PARTICLE_SIZE / 2;
        
        Vector3D pos = adjParticlePos(p->pos);
        
        glTexCoord2f(0, 0);
        glVertex3f(pos[0] - size, pos[1] - size, pos[2]);
        glTexCoord2f(0, 1);
        glVertex3f(pos[0] - size, pos[1] + size, pos[2]);
        glTexCoord2f(1, 1);
        glVertex3f(pos[0] + size, pos[1] + size, pos[2]);
        glTexCoord2f(1, 0);
        glVertex3f(pos[0] + size, pos[1] - size, pos[2]);
    }
    glEnd();
}

//==================
// Private Methods
//==================
Vector3D ParticleEngine::curColor() {
    Vector3D color;
    if (colorTime < 0.166667f) {
        color = Vector3D(1.0f, colorTime * 6, 0.0f);
    }
    else if (colorTime < 0.333333f) {
        color = Vector3D((0.333333f - colorTime) * 6, 1.0f, 0.0f);
    }
    else if (colorTime < 0.5f) {
        color = Vector3D(0.0f, 1.0f, (colorTime - 0.333333f) * 6);
    }
    else if (colorTime < 0.666667f) {
        color = Vector3D(0.0f, (0.666667f - colorTime) * 6, 1.0f);
    }
    else if (colorTime < 0.833333f) {
        color = Vector3D((colorTime - 0.666667f) * 6, 0.0f, 1.0f);
    }
    else {
        color = Vector3D(1.0f, 0.0f, (1.0f - colorTime) * 6);
    }
    
    //Make sure each of the color's components range from 0 to 1
    for(int i = 0; i < 3; i++) {
        if (color[i] < 0) {
            color[i] = 0;
        }
        else if (color[i] > 1) {
            color[i] = 1;
        }
    }
    
    return color;
}

//Returns the average velocity of particles produced by the fountain.
Vector3D ParticleEngine::curVelocity() {
    return Vector3D(2 * cos(angle), 2.0f, 2 * sin(angle));
}

//Alters p to be a particle newly produced by the fountain.
void ParticleEngine::createParticle(Particle* p) {
    p->pos = Vector3D(0, 0, 0);
    p->velocity = curVelocity() + Vector3D(0.5f * randomFloat() - 0.25f,
                                           0.5f * randomFloat() - 0.25f,
                                           0.5f * randomFloat() - 0.25f);
    p->color = curColor();
    p->timeAlive = 0;
    p->lifespan = randomFloat() + 1;
}

//Advances the particle fountain by STEP_TIME seconds.
void ParticleEngine::step() {
    colorTime += STEP_TIME / 10;
    while (colorTime >= 1) {
        colorTime -= 1;
    }
    
    angle += 0.5f * STEP_TIME;
    while (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    
    for(int i = 0; i < NUM_PARTICLES; i++) {
        Particle* p = particles + i;
        
        p->pos = p->pos + STEP_TIME * p->velocity;
        p->velocity = p->velocity + Vector3D(0.0f, -GRAVITY * STEP_TIME, 0.0f);
        p->timeAlive += STEP_TIME;
        if (p->timeAlive > p->lifespan) {
            createParticle(p);
        }
    }
}

