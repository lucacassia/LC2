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
double angle = 0;

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
   glFrustum (-w*0.5/h, w*0.5/h, -0.5, 0.5, 0.5, 2.0);
   glMatrixMode (GL_MODELVIEW);
}

void displayF()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 1.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glutWireCube (1.0);
    int k;
    glTranslatef(-0.5, -0.5, -0.5);
    for(k = 0; k < N; k++){
        if((k==collider1)||(k==collider2)) drawSphere(particle[k].r,SIGMA/2,VEC3(1.0,0.2,0.2));
        else drawSphere(particle[k].r,SIGMA/2,VEC3(0.2,0.2,0.2));
    }
    glutSwapBuffers();
}

void glInit()
{
  GLfloat light_ambient[] =
  {0.1, 0.1, 0.1, 1.0};
  GLfloat light_diffuse[] =
  {0.1, 0.1, 0.1, 1.0};
  GLfloat light_specular[] =
  {0.1, 0.1, 0.1, 1.0};
  GLfloat light_position[] =
  {0.0, 0.0, 10.0, 0.0};

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
        case ' ':
            run();
            break;
        case '+':
            printf("\nETA = %lf\n",ETA *= 1.1);
            init();
            break;
        case '-':
            printf("\nETA = %lf\n",ETA /= 1.1);
            init();
            break;
        case 'n':
            N++;
            init();
            break;
        case 'N':
            if(N > 0) N--;
            init();
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'r': case 'R':
            init();
            break;
        case 'p': case 'P':
            print();
            break;
        case 'q': case 'Q': case 27:
            free(particle);
            free(ctimes);
            exit(0);
            break;
    }
}

void specialKeyboardF(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F11:
            glutFullScreenToggle();
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            angle += 1;
            break;
        case GLUT_KEY_RIGHT:
            angle -= 1;
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
    glutSpecialFunc(specialKeyboardF);
    glutReshapeFunc(reshapeF);

    glutMainLoop();
    return 0;
}

