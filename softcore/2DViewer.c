#include<GL/freeglut.h>

#define DIMENSION 3

#include "softcore.h"

#define PI 3.1415926535897932384626433832795
 
int WIDTH  = 600;
int HEIGHT = 600;

int ACTIVE = 0;
int SINGLE_PARTICLE = 0;
int WHICH_PARTICLE = 0;
int SHOW_TABLE = 0;
double FRAME = 0.025;

body *particle = NULL;

void savePPM()
{
    char filename[50];
    sprintf(filename, "hardcore2d_%d_%f.ppm", n_particles, rho);
    FILE *f = fopen(filename,"wb");
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    unsigned char *snapshot = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));
    glReadPixels(0,0,WIDTH,HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,snapshot);
    fwrite(snapshot, sizeof(unsigned char), 3 * WIDTH * HEIGHT, f);
    free(snapshot);
    fclose(f);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 'p': case 'P':
            printf("N: %d\n",n_particles);
            printf("rho: %f\n",rho);
            printf("Runtime: %f\n",runtime);
            printf("time_step: %f\n",time_step);
            printf("T = %f\n",T);
            printf("H = %f\n",H);
            printf("K = %f\n",K);
            printf("U = %f\n",U);
            savePPM();
            break;
        case ' ':
            ACTIVE = !ACTIVE;
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'q': case 'Q': case 27:
            clear(particle);
            exit(0);
            break;
    }
}

void specialKeyboard(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_F1:
            SINGLE_PARTICLE = !SINGLE_PARTICLE;
            break;
        case GLUT_KEY_F2:
            WHICH_PARTICLE = (WHICH_PARTICLE+1)%n_particles;
            break;
        case GLUT_KEY_F3:
            SHOW_TABLE = !SHOW_TABLE;
            break;
        case GLUT_KEY_F11:
            glutFullScreenToggle();
            break;
        case GLUT_KEY_UP:
            time_step *= 1.1;
            break;
        case GLUT_KEY_DOWN:
            time_step /= 1.1;
            break;
        case GLUT_KEY_LEFT:
            rho /= 1.1;
            init(particle);
            break;
        case GLUT_KEY_RIGHT:
            rho *= 1.1;
            init(particle);
            break;
    }
}

void idle(void)
{
    if(ACTIVE) integrate(particle);
    glutPostRedisplay();
}

void initGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0-FRAME, 1.0+FRAME, 0.0-FRAME, 1.0+FRAME);
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
        gluOrtho2D((0.0-FRAME)-(WIDTH-HEIGHT)*(1+2*FRAME)/(2*HEIGHT), (1.0+FRAME)+(WIDTH-HEIGHT)*(1+2*FRAME)/(2*HEIGHT), 0.0-FRAME, 1.0+FRAME);
    else
        gluOrtho2D(0.0-FRAME, 1.0+FRAME, (0.0-FRAME)-(HEIGHT-WIDTH)*(1+2*FRAME)/(2*WIDTH), (1.0+FRAME)+(HEIGHT-WIDTH)*(1+2*FRAME)/(2*WIDTH));
}

void drawCircle(double *pos, double radius, char *color)
{
    double i;
    glColor3ub(color[0],color[1],color[2]);
    glBegin(GL_POLYGON);
    for(i=0;i<2*PI;i+=PI/24)
        glVertex2f(0.5+PBC(pos[0])/L+cos(i)*radius/L,0.5+PBC(pos[1])/L+sin(i)*radius/L);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE_ARB);

    char normal[3] = {33,102,172};
/*    char bright[3] = {127,205,187};*/
    char dark[3] = {8,29,88};
    char halo[3] = {237,248,177};
    char halo1[3] = {255,255,217};
    int i;
    if(SINGLE_PARTICLE){
        drawCircle(particle[WHICH_PARTICLE].pos,Rc+0.3,halo1);
        drawCircle(particle[WHICH_PARTICLE].pos,Rc,halo);
/*        if(SHOW_TABLE){
            for(i = 0; i < neighbor[i][0]; i++)
                drawCircle(particle[neighbor[WHICH_PARTICLE][i+1]].pos,1,bright);
        }else{for(i = 0; i < n_particles; i++) drawCircle(particle[i].pos,1,bright);}*/
        drawCircle(particle[WHICH_PARTICLE].pos,1,dark);
    }else for(i = 0; i < n_particles; i++) drawCircle(particle[i].pos,1,normal);

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
    n_particles = 108;
    rho = 0.7;
    T = 1.19;
    time_step = 0.001;
    particle = (body*)malloc(n_particles*sizeof(body));
    init(particle);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("OpenGL - SoftCore2D");
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

