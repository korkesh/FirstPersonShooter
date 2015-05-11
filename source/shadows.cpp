//
//  shadows.cpp
//  Source: http://www.paulsprojects.net/tutorials/smt/smt.html
//

#include <GLUT/glut.h>
#include <math.h>
#include <sstream>

#include "shadows.h"
#include "shadowMapping.h"
#include "Maths/Maths.h"
#include "algebra.hpp"

//Camera & light positions
Vector3D cameraPosition = Vector3D(0.5f, 1.5f, -2.5f);
GLfloat lightPosition[] = {3.0f, 2.0f, -3.5f, 1.0f};

//Size of shadow map
const int shadowMapSize = 768;

//Textures
GLuint shadowMapTexture;

//Matrices
MATRIX4X4 lightProjectionMatrix, lightViewMatrix;
MATRIX4X4 cameraProjectionMatrix, cameraViewMatrix;

void initializeShadows()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
	//Create the shadow map texture
	glGenTextures(1, &shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	//Calculate & save matrices
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(60.0f, (float)1024/768, 1.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
	
	glLoadIdentity();
	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);
	
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);
	
	glLoadIdentity();
	gluLookAt(lightPosition[0], lightPosition[1], lightPosition[2],
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);
	
	glPopMatrix();
}

void drawBlock(float x, float y, float z)
{
    glPushMatrix();
    
    glTranslatef(x, y, z);
    // Block
    glPushMatrix();
    glScalef(0.75, 0.3, 0.5);
    glTranslatef(0.0, 1.0, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Pips
    glPushMatrix();
    glTranslatef(0.2, 0.45, 0.15);
    glutSolidSphere(0.09, 24, 24);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.2, 0.45, -0.05);
    glutSolidSphere(0.09, 24, 24);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.45, 0.15);
    glutSolidSphere(0.09, 24, 24);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.45, -0.05);
    glutSolidSphere(0.09, 24, 24);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.2, 0.45, 0.15);
    glutSolidSphere(0.09, 24, 24);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.2, 0.45, -0.05);
    glutSolidSphere(0.09, 24, 24);
    glPopMatrix();
    
    glPopMatrix();

}

void drawLogo()
{
    // Red Lego Block
    glColor3f(1.0, 0.0, 0.0);
    drawBlock(0, -0.15, 0);
    
    // Green Lego Block
    glColor3f(0.0, 1.0, 0.0);
    drawBlock(0.75, -0.15, 0);
    
    // Blue Lego Block
    glColor3f(0.0, 0.0, 1.0);
    drawBlock(0.5, 0.15, 0);

    // White Lego Block
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    drawBlock(0.5, -0.15, -1);
    glPopMatrix();
    
    // Base
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();

    glBegin(GL_QUADS);
    glVertex3f(-60,0,-60);
	glVertex3f(-60,0, 60);
	glVertex3f( 60,0, 60);
	glVertex3f( 60,0,-60);
	glEnd();
    
    glPopMatrix();
}

void drawText()
{
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1028, 0.0, 768);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glColor3f(0.5, 0.8, 0.5);
    glRasterPos2i(360, 250);
    
    std::stringstream ss;
    ss << "A Building Block Production";
    
    std::string s = ss.str();
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

}

void renderShadows()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // Render the Scene From the Lights Perspective
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(lightProjectionMatrix);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(lightViewMatrix);
    
    glViewport(0, 0, shadowMapSize, shadowMapSize);
    glCullFace(GL_FRONT);
    drawLogo();
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);
    glCullFace(GL_BACK);
    
    // Render the Scene from the Camera's Perspective
    glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(cameraProjectionMatrix);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(cameraViewMatrix);
    
	glViewport(0, 0, 1024, 768);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT1, GL_AMBIENT, white*0.2f);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white*0.2f);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	drawLogo();

    // Render the Shadows (See Book Reference in Documentation)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    
	static MATRIX4X4 viewPort(0.5f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.5f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.5f, 0.0f,
								0.5f, 0.5f, 0.5f, 1.0f);
	MATRIX4X4 textureMatrix = viewPort * lightProjectionMatrix * lightViewMatrix;
    
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);
    
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);
    
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);
    
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);
    
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);
    glAlphaFunc(GL_GEQUAL, EPSILON);
	glEnable(GL_ALPHA_TEST);
    
	drawLogo();
    
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
    glDisable(GL_ALPHA_TEST);
    
    drawText();
    
	//reset matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
    
	glutSwapBuffers();
}

