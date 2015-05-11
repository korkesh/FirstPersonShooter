//
//  generateWorld.cpp
//  openGLTutorial
//
//  Created by Matthew Correia on 2014-07-12.
//  Copyright (c) 2014 Matthew Correia. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

#include "generateWorld.h"

#define CAMERA_RADIUS (0.5)
#define EPSILON (0.9999)

typedef struct Vertex
{
	float x, y, z;
	float u, v;
} vertex;

typedef struct Triangle
{
	vertex vertex[3];
    GLuint texture;
} triangle;

typedef struct Square
{
	vertex vertex[4];
    GLuint texture;
} square;


//typedef struct Sector
//{
//	int numtriangles;
//	triangle* triangle;
//} sector;

typedef struct Sector
{
	int numSquares;
	square* square;
} sector;


sector sector1;

// Source: http://nehe.gamedev.net/tutorial/loading_and_moving_through_a_3d_world/22003/
void readstr(FILE *f, char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n') || (string[0] == '\r'));
    
	return;
}

void SetupWorld()
{
	float x, y, z, u, v;
    int t;
	int numsquares;
	FILE *filein;
	char oneline[255];
	filein = fopen("/Users/Korkesh/Documents/Coding Projects/openGLTutorial/World.txt", "rt"); // File To Load World Data From
    
	readstr(filein, oneline);
	sscanf(oneline, "NUMPOLLIES %d\n", &numsquares);
    
	sector1.square = new square[numsquares];
	sector1.numSquares = numsquares;
	for (int i = 0; i < numsquares; i++)
	{
		for (int vert = 0; vert < 4; vert++)
		{
			readstr(filein, oneline);
			sscanf(oneline, "%f %f %f %f %f %d", &x, &y, &z, &u, &v, &t);
			sector1.square[i].vertex[vert].x = x;
			sector1.square[i].vertex[vert].y = y;
			sector1.square[i].vertex[vert].z = z;
			sector1.square[i].vertex[vert].u = u;
			sector1.square[i].vertex[vert].v = v;
            sector1.square[i].texture = t;
		}
	}
    
	fclose(filein);
	return;
}

// Source: http://nehe.gamedev.net/tutorial/loading_and_moving_through_a_3d_world/22003/
void drawSceneFromFile(GLuint* textures)
{
	GLfloat x_m, y_m, z_m, u_m, v_m;
    
	int numsquares;
    numsquares = sector1.numSquares;
	
    glColor3f(1.0, 1.0, 1.0);
	// Process Each Triangle
	for (int i = 0; i < numsquares; i++)
	{
        glBindTexture(GL_TEXTURE_2D, textures[sector1.square[i].texture]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glPushMatrix();
		glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f, 1.0f);
        x_m = sector1.square[i].vertex[0].x;
        y_m = sector1.square[i].vertex[0].y;
        z_m = sector1.square[i].vertex[0].z;
        u_m = sector1.square[i].vertex[0].u;
        v_m = sector1.square[i].vertex[0].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);
        
        x_m = sector1.square[i].vertex[1].x;
        y_m = sector1.square[i].vertex[1].y;
        z_m = sector1.square[i].vertex[1].z;
        u_m = sector1.square[i].vertex[1].u;
        v_m = sector1.square[i].vertex[1].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);
        
        x_m = sector1.square[i].vertex[2].x;
        y_m = sector1.square[i].vertex[2].y;
        z_m = sector1.square[i].vertex[2].z;
        u_m = sector1.square[i].vertex[2].u;
        v_m = sector1.square[i].vertex[2].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);
        
        x_m = sector1.square[i].vertex[3].x;
        y_m = sector1.square[i].vertex[3].y;
        z_m = sector1.square[i].vertex[3].z;
        u_m = sector1.square[i].vertex[3].u;
        v_m = sector1.square[i].vertex[3].v;
        glTexCoord2f(u_m,v_m);
        glVertex3f(x_m,y_m,z_m);
        
		glEnd();
        glPopMatrix();
	}
	return;
}

bool checkCollisions(int xpos, int ypos, int zpos)
{
    
    bool collide = false;
    float radius = 1.0f;
    GLfloat x_m, y_m, z_m;

    Vector3D origin = Vector3D(xpos, ypos, zpos);
    Point3D originP = Point3D(xpos, ypos, zpos);

    // go through all of our triangles
    int numsquares;
    numsquares = sector1.numSquares;
	
	// Process Each Triangle
	for (int i = 0; i < numsquares; i++)
	{
        x_m = sector1.square[i].vertex[0].x;
        y_m = sector1.square[i].vertex[0].y;
        z_m = sector1.square[i].vertex[0].z;
        Vector3D v1 = Vector3D(x_m, y_m, z_m);
        
        x_m = sector1.square[i].vertex[1].x;
        y_m = sector1.square[i].vertex[1].y;
        z_m = sector1.square[i].vertex[1].z;
        Vector3D v2 = Vector3D(x_m, y_m, z_m);
        
        x_m = sector1.square[i].vertex[2].x;
        y_m = sector1.square[i].vertex[2].y;
        z_m = sector1.square[i].vertex[2].z;
        Vector3D v3 = Vector3D(x_m, y_m, z_m);
        
        x_m = sector1.square[i].vertex[3].x;
        y_m = sector1.square[i].vertex[3].y;
        z_m = sector1.square[i].vertex[3].z;
        Vector3D v4 = Vector3D(x_m, y_m, z_m);

        Vector3D square[4] = {v1, v2, v3, v4};
        
        Vector3D A = square[2] - square[0];
        Vector3D B = square[1] - square[0];
        
        Vector3D faceNormal = A.cross(B);
        faceNormal.normalize();
        
        float t = 0.0f;
        double angle = 0.0;

        float d = - (faceNormal.dot(square[0]));
        t = fabs((faceNormal.dot(origin)) + d);
        
        if (t < CAMERA_RADIUS) {
            
            Vector3D offset = t * faceNormal;
            Vector3D intersectionPoint = origin - offset;
            
            for (int i = 0; i < 4; i++)
            {
                A = square[i] - intersectionPoint;
                B = square[(i + 1) % 4] - intersectionPoint;
                
                angle += acos((A.dot(B)) / (sqrtf(A.dot(A)) * sqrtf(B.dot(B))));
            }
            
            if(angle >= (EPSILON * (2.0 * M_PI)) )
            {
                collide = true;
            }
        }

    }
        return collide;
}


