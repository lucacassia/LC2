#include <GL/freeglut.h>
#include <stdio.h>

#define BUFSIZE 512
#define SPHERE  1

void showInfo();
void drawStat();
void drawStuff();
double run();

int SINGLE_PARTICLE = 0;
int WHICH_PARTICLE = 0;


GLuint selectBuf[BUFSIZE];
int h_angle = 0;
int v_angle = 0;
int active = 0;
int WIDTH = 500;
int HEIGHT = 500;
int MODE = 0;

void drawString(int x, int y, char *format,...)
{
    va_list args;
    char buffer[512];
    char *str;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(x, y);

    for (str = buffer; *str; str++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

void drawSphere(double *pos, double radius, double *col)
{
  glPushMatrix();
  glLoadName(SPHERE);
  glPushMatrix();
  GLfloat COLOR[4] = {col[0], col[1], col[2], 0.5};
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, COLOR);
  glColor3f(col[0], col[1], col[2]);
  glTranslatef(pos[0], pos[1], pos[2]);
  glScalef(radius, radius, radius);
  glCallList(SPHERE);
  glPopAttrib();
  glPopMatrix();
}

void reshapeF(int w, int h)
{
    glViewport(0, 0, WIDTH = w, HEIGHT = h); 
}

void displayF()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport (0, 0, (GLsizei) WIDTH, (GLsizei) HEIGHT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-WIDTH * 0.5 / HEIGHT, WIDTH * 0.5 / HEIGHT, -0.5, 0.5, 0.5, 50);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(v_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(h_angle, 0.0f, 1.0f, 0.0f);
    glutWireCube (1.0);
    glTranslatef(-0.5, -0.5, -0.5);
    drawStuff();
    showInfo();
    if(MODE)
        drawStat();
    glFlush();
    glutSwapBuffers();
}

void glInit()
{
  GLfloat light_ambient[]  =  {0.1, 0.1, 0.1, 1.0};
  GLfloat light_diffuse[]  =  {0.1, 0.1, 0.1, 1.0};
  GLfloat light_specular[] =  {0.1, 0.1, 0.1, 1.0};
  GLfloat light_position[] =  {0.0, 0.0, 1.0, 0.0};

  glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
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
  glutSolidSphere(1, 50, 50);
  glEndList();
}

void idleF(void)
{
    if(active) run();
    glutPostRedisplay();
}

void specialKeyboardF(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_F1:
            SINGLE_PARTICLE = !SINGLE_PARTICLE;
            break;
        case GLUT_KEY_F2:
            WHICH_PARTICLE = (WHICH_PARTICLE+1)%n_particles;
            break;
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

