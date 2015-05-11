//
//  target.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-15.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include "target.h"
#include "UI.h"
#include "texture.h"
#include "soundEffects.h"
#include <iostream>

Target targets[NUM_TARGETS];

void initializeTargets()
{
    targets[0].position = Point3D(13, 1, 8);
    targets[0].soundEffect = soundCow;
    
    targets[1].position = Point3D(-13, 3, -8);
    targets[1].soundEffect = soundPig;

    targets[2].position = Point3D(10, 1, -13);
    targets[2].soundEffect = soundCow;
    
    targets[3].position = Point3D(-8, 2, 15);
    targets[3].soundEffect = soundCow;

    targets[4].position = Point3D(0, 3, 0);
    targets[4].soundEffect = soundPig;

    for (int i = 0; i < NUM_TARGETS; i++) {
        targets[i].state = DEFAULT;
//        targets[i].soundEffect = soundDuck;
    }
}

void drawTarget()
{
 	glColor3f(1.0, 0.0, 1.0);
    glDisable(GL_LIGHTING);
    for (int i = 0; i < NUM_TARGETS; i++) {
        glLoadName(i);
        
        if (targets[i].state == DEAD) {
            continue;
        }
        if (targets[i].state == EXPLODING) {
            NewtonEngine(targets[i].position[0], targets[i].position[1], targets[i].position[2]);
            drawParticlesNewton();
            score += 1;
            targets[i].state = DEAD;
            playSound(targets[i].soundEffect);
            continue;
        }
        
        glPushMatrix();
        glTranslatef(targets[i].position[0], targets[i].position[1], targets[i].position[2]);
        
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, texturesEnvironment[2]);
        
        GLUquadricObj* quadratic = gluNewQuadric();
        gluQuadricNormals( quadratic, GLU_SMOOTH );
        gluQuadricTexture( quadratic, GL_TRUE );
        
        gluSphere(quadratic, 0.5f, 32, 32 );
        
        glPopMatrix();
    }
    
    glEnable(GL_LIGHTING);

}
