//
//  texture.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-12.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//
#include <GLUT/GLUT.h>

#include "texture.h"

GLuint textureMenu[6];
GLuint texturesEnvironment[8];
GLuint textureSkybox[6];
GLuint textureParticle;
GLuint textureGun;
GLuint textureCookie;

// Source: http://videotutorialsrock.com/opengl_tutorial/textures/text.php
GLuint loadTextureFromImage(Image *image)
{
    GLuint ID = -1;
    glGenTextures(1, &ID);
    
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    return ID;
    
}

void textures() {
    Image* image;
    
    // Load Menu Textures
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/icon.bmp");
    textureMenu[0] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Desktop/CS488/Final Project with Shadows/source/Resources/metal.bmp");
	textureMenu[1] = loadTextureFromImage(image);
	delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/robot.bmp");
	textureMenu[2] = loadTextureFromImage(image);
	delete image;
    
    image = loadBMP("/Users/Korkesh/Desktop/CS488/Final Project with Shadows/source/Resources/green.bmp");
	textureMenu[3] = loadTextureFromImage(image);
	delete image;
    
    image = loadBMP("/Users/Korkesh/Desktop/CS488/Final Project with Shadows/source/Resources/purple.bmp");
	textureMenu[4] = loadTextureFromImage(image);
	delete image;
    
    image = loadBMP("/Users/Korkesh/Desktop/CS488/Final Project with Shadows/source/Resources/bullet.bmp");
	textureMenu[5] = loadTextureFromImage(image);
	delete image;
    
    
    // Load Enironment textures
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/wall1.bmp");
    texturesEnvironment[0] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/floor1.bmp");
    texturesEnvironment[1] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/crate1.bmp");
    texturesEnvironment[2] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/grass.bmp");
    texturesEnvironment[3] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/brick.bmp");
    texturesEnvironment[4] = loadTextureFromImage(image);
    delete image;

    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/ceiling.bmp");
    texturesEnvironment[5] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/openGLTutorial/brick.bmp");
    texturesEnvironment[6] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Desktop/CS488/Final Project with Shadows/source/Resources/ball.bmp");
    texturesEnvironment[7] = loadTextureFromImage(image);
    delete image;
    
    
    // Load our Skybox textures
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/front.bmp");
    textureSkybox[0] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/back.bmp");
    textureSkybox[1] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/left.bmp");
    textureSkybox[2] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/right.bmp");
    textureSkybox[3] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/up.bmp");
    textureSkybox[4] = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/down.bmp");
    textureSkybox[5] = loadTextureFromImage(image);
    delete image;
    
    // Load particle texture
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/circle.bmp");
	Image* alphaChannel = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/circlealpha.bmp");
	textureParticle = loadAlphaTexture(image, alphaChannel);
	delete image;
	delete alphaChannel;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/comic.bmp");
    textureGun = loadTextureFromImage(image);
    delete image;
    
    image = loadBMP("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/cookie.bmp");
    textureCookie = loadTextureFromImage(image);
    delete image;

}

//Returns an array indicating pixel data for an RGBA image that is the same as
//image, but with an alpha channel indicated by the grayscale image alphaChannel
char* addAlphaChannel(Image* image, Image* alphaChannel) {
	char* pixels = new char[image->width * image->height * 4];
	for(int y = 0; y < image->height; y++) {
		for(int x = 0; x < image->width; x++) {
			for(int j = 0; j < 3; j++) {
				pixels[4 * (y * image->width + x) + j] =
                image->pixels[3 * (y * image->width + x) + j];
			}
			pixels[4 * (y * image->width + x) + 3] =
            alphaChannel->pixels[3 * (y * image->width + x)];
		}
	}
	
	return pixels;
}

//Makes the image into a texture, using the specified grayscale image as an
//alpha channel and returns the id of the texture
GLuint loadAlphaTexture(Image* image, Image* alphaChannel) {
	char* pixels = addAlphaChannel(image, alphaChannel);
	
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGBA,
				 image->width, image->height,
				 0,
				 GL_RGBA,
				 GL_UNSIGNED_BYTE,
				 pixels);
	
	delete pixels;
	return textureId;
}
