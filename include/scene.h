#include <GL/freeglut.h>
#include <stdio.h>

#include "vec3.h"

#define BUFSIZE 512

#define SPHERE	    1

void drawStuff();
void run();

GLuint selectBuf[BUFSIZE];
int h_angle = 0;
int v_angle = 0;
int active = 0;

void print_bitmap_string(double x, double y, double z, char *format,...)
{
    va_list args;
    char buffer[512], *s;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(x, y, z);
    for (s = buffer; *s; s++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *s);
}

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
    glRotatef(v_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(h_angle, 0.0f, 1.0f, 0.0f);
    glutWireCube (1.0);
    glTranslatef(-0.5, -0.5, -0.5);
    drawStuff();
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
  {0.0, 0.0, 1.0, 0.0};

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
    if(active)
        run();
    glutPostRedisplay();
}

void specialKeyboardF(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F11:
            glutFullScreenToggle();
            break;
        case GLUT_KEY_UP:
            v_angle++;
            break;
        case GLUT_KEY_DOWN:
            v_angle--;
            break;
        case GLUT_KEY_LEFT:
            h_angle++;
            break;
        case GLUT_KEY_RIGHT:
            h_angle--;
            break;
    }
}

