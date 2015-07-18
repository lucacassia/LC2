#include<GL/freeglut.h>
#include "hardcore2d.h"

#define PI 3.1415926535897932384626433832795
 
#define WIDTH 600
#define HEIGHT 600

int ACTIVE = 0;

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 'p': case 'P': case ' ':
            ACTIVE = !ACTIVE;
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'q': case 'Q': case 27:
            clear();
            exit(0);
            break;
    }
}

void specialKeyboard(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_F11:
            glutFullScreenToggle();
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
    }
}

void idle(void)
{
    if(ACTIVE) collide();
    glutPostRedisplay();
}

void initGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glClearColor(8/255.0,29/255.0,88/255.0,0.0);
}
 
void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

void drawCircle(double *pos, double radius, double *color)
{
    glColor3f(color[0],color[1],color[2]);
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2*PI; i += PI/24)
        glVertex2f( pos[0] + cos(i) * radius, pos[1] + sin(i) * radius);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE_ARB);

    double normal[3] = {65/255.0,182/255.0,196/255.0};
    double edf8b1[3] = {237/255.0,248/255.0,177/255.0};
    int i;
    for(i = 0; i < n_particles; i++){
        if(i == collider[0]||i == collider[1]) drawCircle(particle[i].pos,SIGMA/2,edf8b1);
        else drawCircle(particle[i].pos,SIGMA/2,normal);
    }
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    if(init( 0.1f, 1.0f )) return 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("OpenGL - HardCore2D");
    initGL();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeFunc(reshape);

    printf("%s\n",glGetString(GL_RENDERER));

    glutMainLoop();
    return 0;
}

