#include<GL/freeglut.h>
#include "opengl.h"

#define PI 3.1415926535897932384626433832795
 
#define WIDTH 600
#define HEIGHT 600

int ACTIVE = 0;
double frame = 0.025;

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 'p': case 'P':
            printf("Pressure: %f\n",get_pressure());
            printf("Collisions: %d\n",n_collisions);
            printf("Runtime: %f\n",runtime);
            printf("Mean Free Path: %f\n",get_mean_free_path());
            print_pos();
            print_mom();
            print_distribution();
            break;
        case ' ':
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
    if(ACTIVE) run();
    glutPostRedisplay();
}

void initGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0-frame, 1.0+frame, 0.0-frame, 1.0+frame);
    glClearColor(1.0,1.0,1.0,0.0);
}
 
void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(width > height)
        gluOrtho2D((0.0-frame)-(width-height)*(1+2*frame)/(2*height), (1.0+frame)+(width-height)*(1+2*frame)/(2*height), 0.0-frame, 1.0+frame);
    else
        gluOrtho2D(0.0-frame, 1.0+frame, (0.0-frame)-(height-width)*(1+2*frame)/(2*width), (1.0+frame)+(height-width)*(1+2*frame)/(2*width));
}

void drawCircle(double *pos, double radius, char *color)
{
    double i;
    glColor3ub(color[0],color[1],color[2]);
    glBegin(GL_POLYGON);
    for(i = 0; i < 2*PI; i += PI/24)
        glVertex2f( pos[0] + cos(i) * radius, pos[1] + sin(i) * radius);
    glEnd();
    if(pos[0]+radius > 1.0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]-1.0+cos(i)*radius,pos[1]+sin(i)*radius);glEnd();}
    if(pos[0]-radius > 1.0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]+1.0+cos(i)*radius,pos[1]+sin(i)*radius);glEnd();}
    if(pos[1]+radius > 1.0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]+cos(i)*radius,pos[1]-1.0+sin(i)*radius);glEnd();}
    if(pos[1]-radius > 1.0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]+cos(i)*radius,pos[1]+1.0+sin(i)*radius);glEnd();}

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE_ARB);

    char normal[3] = {33,102,172};
    char bright[3] = {255,0,0};
    int i;
    for(i = 0; i < n_particles; i++){
        if(i == collider[0]||i == collider[1])
            drawCircle(particle[i].pos,SIGMA/2,bright);
        else drawCircle(particle[i].pos,SIGMA/2,normal);
    }

    /* draw frame */
    glColor3ub(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0,0.0);
        glVertex2f(1.0,0.0);
        glVertex2f(1.0,1.0);
        glVertex2f(0.0,1.0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    if(init( 0.2f, 1.0f )) return 1;

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

    printf("%s\n%s\n",glGetString(GL_RENDERER),glGetString(GL_VERSION));

    glutMainLoop();
    return 0;
}

