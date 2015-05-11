//
//  texture.h
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-12.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#ifndef __openGLTutorial__texture__
#define __openGLTutorial__texture__

#include "imageloader.h"

extern GLuint textureMenu[6];
extern GLuint texturesEnvironment[8];
extern GLuint textureSkybox[6];
extern GLuint textureParticle;
extern GLuint textureGun;
extern GLuint textureCookie;

void textures();
char* addAlphaChannel(Image* image, Image* alphaChannel);
GLuint loadAlphaTexture(Image* image, Image* alphaChannel);

#endif /* defined(__openGLTutorial__texture__) */
