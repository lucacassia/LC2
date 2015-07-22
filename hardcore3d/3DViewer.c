#include <GL/freeglut.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "hardcore3d.h"

#define BUFSIZE 512
#define SPHERE  1

int SINGLE_PARTICLE = 0;
int WHICH_PARTICLE = 0;

GLuint selectBuf[BUFSIZE];
int h_angle = 0;
int v_angle = 0;
int active = 0;
int width = 500;
int height = 500;
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
    glViewport(0, 0, width = w, height = h); 
}

void showInfo()
{
    /* backup current model-view matrix */
    glPushMatrix();
    glLoadIdentity();

    /* set to 2D orthogonal projection */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    int h = height, dh = 18;
    drawString(1, h-=dh, "Particles: %d", n_particles);
    drawString(1, h-=dh, "Eta = %lf", ETA);
    drawString(1, h-=dh, "Runtime = %lf", runtime);
    drawString(1, h-=dh, "Collisions = %d", n_collisions);
    drawString(1, h-=dh, "Pressure = %lf", get_pressure());

    /* restore projection matrix */
    glPopMatrix();

    /* restore modelview matrix */
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void drawStuff()
{
    int k;
    double red[3] = {1.0,0.2,0.2};
    double grey[3] = {0.2,0.2,0.2};
    if(SINGLE_PARTICLE){
        if((WHICH_PARTICLE==collider[0])||(WHICH_PARTICLE==collider[1]))
            drawSphere(particle[WHICH_PARTICLE].pos, SIGMA/2, red);
        else
            drawSphere(particle[WHICH_PARTICLE].pos, SIGMA/2, grey);
    }else
        for(k = 0; k < n_particles; k++){
            if((k==collider[0])||(k==collider[1]))
                drawSphere(particle[k].pos, SIGMA/2, red);
            else
                drawSphere(particle[k].pos, SIGMA/2, grey);
        }
    showInfo();
}

void displayF()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-width * 0.5 / height, width * 0.5 / height, -0.5, 0.5, 0.5, 50);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(v_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(h_angle, 0.0f, 1.0f, 0.0f);
    glutWireCube (1.0);
    glTranslatef(-0.5, -0.5, -0.5);
    drawStuff();
    showInfo();
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


void savePPM()
{
    char filename[50];
    sprintf(filename, "hardcore3d_%d_%f.ppm", n_particles, ETA);
    FILE *f = fopen(filename,"wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);
    unsigned char *snapshot = (unsigned char*)malloc(3*width*height*sizeof(unsigned char));
    glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,snapshot);
    fwrite(snapshot, sizeof(unsigned char), 3 * width * height, f);
    free(snapshot);
    fclose(f);
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

void keyboardF(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':
            active = !active;
            break;
        case '+':
            ETA *= 1.1;
            init(ETA,1.0f);
            break;
        case '-':
            ETA /= 1.1;
            init(ETA,1.0f);
            break;
        case 'n':
            clear();
            n_particles += 2;
            init(ETA,1.0f);
            break;
        case 'N':
            clear();
            if(n_particles >= 2) n_particles -= 2;
            init(ETA,1.0f);
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'v': case 'V':
            v_angle = h_angle = 0;
            break;
        case 'i': case 'I':
            init(ETA,1.0f);
            break;
        case 'p': case 'P':
            printf("Collisions: %d\t",n_collisions);
            printf("Runtime: %f\n",runtime);
            savePPM();
            break;
        case 'r': case 'R':
            reset();
            break;
        case 'q': case 'Q': case 27:
            clear();
            exit(0);
            break;
    }
}

void idleF(void)
{
    if(active) run();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL - HardCore3D");

    srand(time(NULL));
    glInit();
    init(0.5,1.0f);

    glutDisplayFunc(displayF);
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutSpecialFunc(specialKeyboardF);
    glutReshapeFunc(reshapeF);

    glutMainLoop();
    return 0;
}

