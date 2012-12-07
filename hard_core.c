#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/freeglut.h>
#include "hard_core.h"

#define BUFSIZE 512

#define SPHERE	    1

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
    int k;
    glTranslatef(-0.5, -0.5, -0.5);
    for(k = 0; k < N; k++){
        if((k==collider1)||(k==collider2)) drawSphere(particle[k].r,SIGMA/2,VEC3(1.0,0.2,0.2));
        else drawSphere(particle[k].r,SIGMA/2,VEC3(0.2,0.2,0.2));
    }
    double h = 1.0, dh = 0.05;
    print_bitmap_string(0.0, h-=dh, 1.0, "Particles: %d", N);
    print_bitmap_string(0.0, h-=dh, 1.0, "Eta = %lf", ETA);
    print_bitmap_string(0.0, h-=dh, 1.0, "Sigma = %lf", SIGMA);
    print_bitmap_string(0.0, h-=dh, 1.0, "Temperature = %lf", temperature);
    print_bitmap_string(0.0, h-=dh, 1.0, "Runtime = %lf", runtime);
    print_bitmap_string(0.0, h-=dh, 1.0, "Pressure = %lf", pressure);
    print_bitmap_string(0.0, h-=dh, 1.0, "Hits = %d", hits);
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

void keyboardF(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':
            active = !active;
            break;
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
        case 'N':
            if(N > 0) N--;
            init();
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'v': case 'V':
            v_angle = h_angle = 0;
            break;
        case 'r': case 'R':
            reset();
            break;
        case 'i': case 'I':
            init();
            break;
        case 'p': case 'P':
            print();
            break;
        case 'q': case 'Q': case 27:
            clear();
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("hard core");

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

