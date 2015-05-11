//
//  soundEffects.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-07-18.
//
//

#ifndef __opengl_series__soundEffects__
#define __opengl_series__soundEffects__

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <iostream>

extern ALCdevice *device;
extern ALCcontext *context;
extern ALuint soundCollision, soundExplosion, soundCow, soundPig, soundDuck;
extern ALuint bufferCollision, bufferExplosion, bufferCow, bufferPig, bufferDuck;
extern ALsizei size, freq;
extern ALenum format;
extern ALvoid *data;

void playSound(ALuint sound);
void sound(int xpos, int zpos);

#endif /* defined(__opengl_series__soundEffects__) */
