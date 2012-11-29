#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/freeglut.h>
#include "hard_kernel.h"

#define BUFSIZE 512

#define SPHERE	    1

GLuint selectBuf[BUFSIZE];

void drawSphere(vec3 p,double r,vec3 c)
{
  glPushMatrix();
  glLoadName(SPHERE);
  glPushMatrix();
  GLfloat COLOR[4] = {c.x, c.y, c.z, 0.5};
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, COLOR);
  glColor3f(c.x, c.y, c.z);
  glTranslatef(p.x, p.y, p.z);
  glScalef(r, r, r);
  glCallList(SPHERE);
  glPopAttrib();
  glPopMatrix();
}
void reshapeF(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-0.5, 0.5, -0.5, 0.5, 0.5, 5.0);
   glMatrixMode (GL_MODELVIEW);
}

void displayF()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutWireCube (1.0);
    int k;
    glTranslatef(-0.5, -0.5, -0.5);
    for(k = 0; k < N; k++){
        drawSphere(particle[k].r,SIGMA/2,particle[k].c);
    }
    glutSwapBuffers();
}

void glInit()
{
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    reshapeF(viewport[2],viewport[3]);

  GLfloat light_ambient[] = {0.2, 0.2, 1.0, 1.0};
  GLfloat light_diffuse[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat light_specular[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat light_position[] = {0.0, 0.0, 5, 0.0};

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glDepthFunc(GL_LEQUAL);
  glClearDepth(1.0f);

  glSelectBuffer(BUFSIZE, selectBuf);

  glNewList(SPHERE, GL_COMPILE);
  glutSolidSphere(1, 100, 100);
  glEndList();
}

void idleF(void)
{
    glutPostRedisplay();
}

void keyboardF(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+':
            ETA *= 1.1;
            init();
            break;
        case '-':
            ETA /= 1.1;
            init();
            break;
        case 'n':
            N++;
            init();
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'r': case 'R':
            init();
            break;
        case 'q': case 'Q': case 27:
            free(particle);
            free(ctimes);
            exit(0);
            break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("scene");

    srand(time(NULL));
    glInit();
    init();

    glutDisplayFunc(displayF);
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutReshapeFunc(reshapeF);

    glutMainLoop();
    return 0;
}

