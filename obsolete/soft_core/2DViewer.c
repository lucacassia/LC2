#include<GL/freeglut.h>
#include "softcore2d.h"

#define PI 3.1415926535897932384626433832795
 
int WIDTH  = 600;
int HEIGHT = 600;

int ACTIVE = 0;
int SINGLE_PARTICLE = 0;
int WHICH_PARTICLE = 0;
int SHOW_TABLE = 0;
double FRAME = 0.025;

void savePPM()
{
    char filename[50];
    sprintf(filename, "hardcore2d_%d_%f.ppm", n_particles, RHO);
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
            printf("RHO: %f\n",RHO);
            printf("Runtime: %f\n",runtime);
            printf("time_step: %f\n",time_step);
            printf("momentum: %f\n",get_total_momentum());
            printf("T = %f\n",T);
            printf("H = %f\n",H);
            printf("K = %f\n",K);
            printf("U = %f\n",U);
            savePPM();
            break;
        case 'r': case 'R':
            reset();
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
            RHO /= 1.1;
            init(n_particles,RHO,1);
            break;
        case GLUT_KEY_RIGHT:
            RHO *= 1.1;
            init(n_particles,RHO,1);
            break;
    }
}

void idle(void)
{
    if(ACTIVE) integrate();
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
        glVertex2f(pos[0]/box_size+cos(i)*radius/box_size,pos[1]/box_size+sin(i)*radius/box_size);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE_ARB);

    char normal[3] = {33,102,172};
    char bright[3] = {127,205,187};
    char dark[3] = {8,29,88};
    char halo[3] = {237,248,177};
    char halo1[3] = {255,255,217};
    int i;
    if(SINGLE_PARTICLE){
        drawCircle(particle[WHICH_PARTICLE].pos,R_C+0.3,halo1);
        drawCircle(particle[WHICH_PARTICLE].pos,R_C,halo);
        if(SHOW_TABLE){
            for(i = 0; i < neighbor[i][0]; i++)
                drawCircle(particle[neighbor[WHICH_PARTICLE][i+1]].pos,1,bright);
        }else{for(i = 0; i < n_particles; i++) drawCircle(particle[i].pos,1,bright);}
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
    time_step = 0.001;
    init( 108, 0.7, 1.19f );

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

