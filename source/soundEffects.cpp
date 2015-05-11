//
//  soundEffects.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-07-18.
//
//

#include "soundEffects.h"
#include "sound.h"

ALCdevice *device;
ALCcontext *context;
ALuint soundCollision, soundExplosion, soundCow, soundPig, soundDuck;
ALuint bufferCollision, bufferExplosion, bufferCow, bufferPig, bufferDuck;
ALsizei size, freq;
ALenum format;
ALvoid *data;


void playSound(ALuint sound)
{
    alSourcePlay(sound);
    // *********This blocks main thread******
    //    ALint source_state;
    //    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    //    while (source_state == AL_PLAYING) {
    //        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    //    }
}

void sound(int xpos, int zpos)
{
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    
    alGenSources(1, &soundCollision);
    alSourcef(soundCollision, AL_PITCH, 1);
    alSourcef(soundCollision, AL_GAIN, 1);
    alSource3f(soundCollision, AL_POSITION, xpos, 0, zpos);
    alSourcei(soundCollision, AL_LOOPING, AL_FALSE);
    
    // Load .Wav file
    if (loadWavFile("/Users/Korkesh/Downloads/FirstPersonShooter/laser.wav", &bufferCollision, &size, &freq, &format) == false) {
        std::cerr << "COLLIDE!" << std::endl;
    }
    
    alSourcei(soundCollision, AL_BUFFER, bufferCollision);
    
    
    alGenSources(2, &soundExplosion);
    alSourcef(soundExplosion, AL_PITCH, 1);
    alSourcef(soundExplosion, AL_GAIN, 0.5);
    alSource3f(soundExplosion, AL_POSITION, xpos, 0, zpos);
    alSourcei(soundExplosion, AL_LOOPING, AL_FALSE);
    
    // Load .Wav file
    if (loadWavFile("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/explosion.wav", &bufferExplosion, &size, &freq, &format) == false) {
        std::cerr << "COLLIDE!" << std::endl;
    }
    
    alSourcei(soundExplosion, AL_BUFFER, bufferExplosion);
    
    
    
    alGenSources(3, &soundCow);
    alSourcef(soundCow, AL_PITCH, 1);
    alSourcef(soundCow, AL_GAIN, 3);
    alSource3f(soundCow, AL_POSITION, xpos, 0, zpos);
    alSourcei(soundCow, AL_LOOPING, AL_FALSE);
    
    // Load .Wav file
    if (loadWavFile("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/cow.wav", &bufferCow, &size, &freq, &format) == false) {
        std::cerr << "COLLIDE!" << std::endl;
    }
    
    alSourcei(soundCow, AL_BUFFER, bufferCow);

    
    
    alGenSources(4, &soundPig);
    alSourcef(soundPig, AL_PITCH, 1);
    alSourcef(soundPig, AL_GAIN, 0.3);
    alSource3f(soundPig, AL_POSITION, xpos, 0, zpos);
    alSourcei(soundPig, AL_LOOPING, AL_FALSE);

    // Load .Wav file
    if (loadWavFile("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/pig.wav", &bufferPig, &size, &freq, &format) == false) {
        std::cerr << "COLLIDE!" << std::endl;
    }
    
    alSourcei(soundPig, AL_BUFFER, bufferPig);
    
    
    alGenSources(5, &soundDuck);
    alSourcef(soundDuck, AL_PITCH, 1);
    alSourcef(soundDuck, AL_GAIN, 1);
    alSource3f(soundDuck, AL_POSITION, xpos, 0, zpos);
    alSourcei(soundDuck, AL_LOOPING, AL_FALSE);
    
    // Load .Wav file
    if (loadWavFile("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/duck.wav", &bufferDuck, &size, &freq, &format) == false) {
        std::cerr << "COLLIDE!" << std::endl;
    }
    
    alSourcei(soundDuck, AL_BUFFER, bufferDuck);

    
}