// Library Headers
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <cstdlib>
#include <ctime>

// Local Headers
#include "generateWorld.h"
#include "texture.h"
#include "algebra.hpp"
#include "sound.h"
#include "skybox.h"
#include "particleNewton.h"
#include "collision.h"
#include "target.h"
#include "UI.h"
#include "animation.h"
#include "shadows.h"
#include "shadowMapping.h"
#include "soundEffects.h"

#define KEY_ESC (27)
#define KEY_SPACE (32)
#define WIDTH (1024)
#define HEIGHT (768)
#define FPS (20)
#define PICK_BUFFER_SIZE (512)
#define MIN_DEPTH (0xffffffff)

float prevXpos = 0, prevYpos = 1.5, prevZpos = 15, prevXrot = 0, prevYrot = 0;
float lastx = WIDTH/2, lasty = HEIGHT/2;

float heading, xpos = 0.0f, ypos = 1.5, zpos = 15.0f;
GLfloat yrot = 0.0f, walkbias = 0, walkbiasangle = 0, lookdown = 0.0f, z = 0.0f;

float timeUntilUpdate = 0;
float lastFire = 0;
float currentFire = 0;

bool displayMenu = false;
bool displayLogo = true;

bool firedGun = false;

void camera () {
    glRotatef(lookdown, 1.0f, 0.0f, 0.0f);
    glRotatef(360.0f - yrot, 0.0f, 1.0f, 0.0f);
    glTranslatef(-xpos, -ypos, -zpos);
}

void lights(){
    
    GLfloat light_position1[] = {10, 10, 10, 1};
    GLfloat light_position2[] = {3, 3, 0, 0};
    
    GLfloat light1[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light2[] = {1.0, 1.0, 1.0, 1.0};
    
    // setup
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glLightModeli(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
    
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 25);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light2);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light2);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 25);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light2);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
}

void lightsMenu(){
    
    GLfloat light_position1[] = {0, 1, 1, 0};
    
    // setup
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
}


void display () {
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
    
    if (displayLogo) {
        glClearColor(0.3, 0.3, 0.3, 1.0);
        renderShadows();
        return;
    }
    
    if (displayMenu) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glTranslatef(0.0f, 0.0f, -2.0f);
        lightsMenu();
        drawMenu();
        glutSwapBuffers();
        return;
    }
    
    // Collision Detection With the Camera
    if (checkCollisions(xpos, ypos, zpos) || testWallCollision(CAMERA, xpos, ypos, zpos) || testCameraCollision(xpos, ypos, zpos))
    {
        xpos = prevXpos;
        ypos = prevYpos;
        zpos = prevZpos;
        
        playSound(soundCollision);
    }
    
    prevXpos = xpos;
    prevYpos = ypos;
    prevZpos = zpos;
    
    // Adjust Lighting
    lights();
    
    // Adjust Camera
    camera();
    
    // Draw Environment
    drawWalls();
    drawSceneFromFile(texturesEnvironment);
    
    // Particle Engine
    drawParticlesNewton();
    
    // Collision Detection Demonstration
    drawBalls();
    
    // Game Targets
    drawTarget();
    
    // Skybox
    drawSkybox(xpos, ypos, zpos);
    
    // UI
    drawUI();
    if (firedGun)
    {
        fireGun();
        if (currentFire - lastFire > 500) {
            firedGun = false;
        }
    }
    
    glutSwapBuffers(); //swap the buffers
}

void update (int t)
{
    stepBalls((float)FPS / 1000.0f, timeUntilUpdate, xpos, ypos, zpos);
    idle(FPS / 1000.0f);
    updateArm(FPS / 1000.0f);
    
    currentFire += FPS;
    
	glutPostRedisplay();
	glutTimerFunc(FPS, update, 0);
    
}

#pragma mark Input
void processHits(GLint hits, GLuint buffer[])
{
    unsigned int i, j;
    GLuint names, *ptr, minZ,*ptrNames = nullptr, numberOfNames = 0;
    
    printf ("hits = %d\n", hits);
    ptr = (GLuint *) buffer;
    minZ = 0xffffffff;
    for (i = 0; i < hits; i++) {
        names = *ptr;
        ptr++;
        if (*ptr < minZ) {
            numberOfNames = names;
            minZ = *ptr;
            ptrNames = ptr+2;
        }
        
        ptr += names+2;
	}
    
    printf ("The closest hit names are ");
    ptr = ptrNames;
    for (j = 0; j < numberOfNames; j++,ptr++) {
        if (displayMenu && (*ptr == 1)) {
            displayMenu = false;
            glutSetCursor(GLUT_CURSOR_NONE);
            continue;
        }
        printf ("%d ", *ptr);
        targets[*ptr].state = EXPLODING;
    }
    printf ("\n");
}

void pickingObjects(int x, int y) {
    
    GLuint selectBuf[PICK_BUFFER_SIZE];
    GLint hits;
    GLint viewport[4];
    
	glSelectBuffer(PICK_BUFFER_SIZE,selectBuf);
	glRenderMode(GL_SELECT);
    
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
	glGetIntegerv(GL_VIEWPORT,viewport);
    
    if (displayMenu) {
        gluPickMatrix(x, viewport[3]-(y), 5, 5, viewport);
    }
    else
    {
        gluPickMatrix(WIDTH/2, viewport[3]-(HEIGHT/2), 5,5, viewport);
    }
    
	gluPerspective(60.0, (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
 	glPushName(0);
    
    glLoadIdentity();
    
    glPushMatrix();
    
    if (displayMenu) {
        glTranslatef(0.0f, 0.0f, -2.0f);
        drawMenu();
    }
    else
    {
        camera();
        drawTarget();
    }
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	
	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);
	
	// if there are hits process them
	if (hits != 0)
		processHits(hits,selectBuf);
}

void keyboard (unsigned char key, int x, int y) {
    if (key =='q')
    {
        heading += 3.0f;
        yrot = heading;
    }
    
    if (key =='e')
    {
        heading -= 3.0f;
        yrot = heading;
    }
    
    if (key =='w')
    {
        xpos -= float(sin(heading * (M_PI / 180)));
        zpos -= float(cos(heading * (M_PI / 180)));
    }
    
    if (key =='s')
    {
        xpos += float(sin(heading * (M_PI / 180)));
        zpos += float(cos(heading * (M_PI / 180)));
    }
    
    if (key =='d')
    {
        xpos += float(cos(heading * (M_PI / 180)));
        zpos -= float(sin(heading * (M_PI / 180)));
    }
    
    if (key =='a')
    {
        xpos -= float(cos(heading * (M_PI / 180)));
        zpos += float(sin(heading * (M_PI / 180)));
    }
    
    if (key == KEY_SPACE) {
        NewtonEngine(xpos, ypos - 1, zpos - 3);
    }
    
    if (key == KEY_ESC)
    {
        exit(0);
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (displayLogo) {
            displayLogo = false;
            displayMenu = true;
            
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            
            glDisable(GL_CULL_FACE);
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glViewport(0, 0, WIDTH, HEIGHT);
            
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0, (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1, 1000.0);

        } else {
            if (score == 5) {
                score = 0;
                initializeTargets();
                xpos = 0.0f;
                zpos = 15.0f;
            }
            else
            {
                playSound(soundExplosion);
                if (displayMenu == false && score >= 0) {
                    firedGun = true;
                    lastFire = currentFire;
                }
                else
                {
                    score += 1;
                }
                pickingObjects(x, y);
            }
        }
    }
    
    glutPostRedisplay();
    
}

void mouseMovement(int x, int y) {
    int diffx = x - lastx;
    int diffy = y - lasty;
    lastx = x;
    lasty = y;
    lookdown += (float) diffy;
    
    if ((lookdown > 90) || (lookdown < -90)) {
        lookdown -= diffy;
    }
    heading += (float) -diffx;
    yrot = heading;
    
    glutPostRedisplay();
}

#pragma mark Initialization & Main Loop
void enable () {
    glEnable (GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_COLOR_MATERIAL);
    
    if (displayLogo) {
        glEnable(GL_CULL_FACE);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    }
}

// Load up all of our assets, data structures, etc.
void init () {
    enable();
    sound(xpos, zpos);
    textures();
    SetupWorld();
    initializeShadows();
    initializeBalls();
    initializeWalls();
    initializeTargets();
    NewtonEngine();
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
 	glViewport(0, 0, WIDTH, HEIGHT);
    
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1, 1000.0);
    
}

void setup()
{
    // initialise GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    // GLEW throws some errors, so discard all the errors so far
    while(glGetError() != GL_NO_ERROR) {}
    
    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
}

int main (int argc, char **argv) {
    srand((unsigned int)time(0));
    
    // Create our Window
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (WIDTH, HEIGHT);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("First Person Shooter Game");
    
    // Set up Callbacks
    glutDisplayFunc (display);
    glutPassiveMotionFunc(mouseMovement); //check for mouse movement
    glutMouseFunc(mouse);
    glutKeyboardFunc (keyboard);
    
    // Initialize
    setup();
    init();
        
    // Start Timer
	glutTimerFunc(FPS, update, 0);
    
    glutMainLoop ();
    return 0;
}