#include<GL/freeglut.h>
#include "hardcore2d.h"

#define PI 3.1415926535897932384626433832795
 
int WIDTH  = 600;
int HEIGHT = 600;

int ACTIVE = 0;
double frame = 0.025;

void savePPM()
{
    char filename[50];
    sprintf(filename, "hardcore2d_%d_%f.ppm", n_particles, ETA);
    FILE *f = fopen(filename,"wb");
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    unsigned char *frame = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));
    glReadPixels(0,0,WIDTH,HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,frame);
    fwrite(frame, sizeof(unsigned char), 3 * WIDTH * HEIGHT, f);
    free(frame);
    fclose(f);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 'p': case 'P':
            printf("Collisions: %d\t",n_collisions);
            printf("Runtime: %f\n",runtime);
            savePPM();
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
            break;
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
 
void reshape(int w, int h)
{
    WIDTH = w;
    HEIGHT = h;
    glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(WIDTH > HEIGHT)
        gluOrtho2D((0.0-frame)-(WIDTH-HEIGHT)*(1+2*frame)/(2*HEIGHT), (1.0+frame)+(WIDTH-HEIGHT)*(1+2*frame)/(2*HEIGHT), 0.0-frame, 1.0+frame);
    else
        gluOrtho2D(0.0-frame, 1.0+frame, (0.0-frame)-(HEIGHT-WIDTH)*(1+2*frame)/(2*WIDTH), (1.0+frame)+(HEIGHT-WIDTH)*(1+2*frame)/(2*WIDTH));
}

void drawCircle(double *pos, double radius, char *color)
{
    double i;
    glColor3ub(color[0],color[1],color[2]);
    glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]+cos(i)*radius,pos[1]+sin(i)*radius);glEnd();
    glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]-1.0+cos(i)*radius,pos[1]+sin(i)*radius);glEnd();
    glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]+1.0+cos(i)*radius,pos[1]+sin(i)*radius);glEnd();
    glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]+cos(i)*radius,pos[1]-1.0+sin(i)*radius);glEnd();
    glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f(pos[0]+cos(i)*radius,pos[1]+1.0+sin(i)*radius);glEnd();

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
    n_particles = 100;
    if(init( 0.3f, 1.0f )) return 1;

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

