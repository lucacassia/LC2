#include<GL/freeglut.h>

#define DIMENSION 2

#include "softcore.h"

#define PI 3.1415926535897932384626433832795
 
int WIDTH  = 600;
int HEIGHT = 600;

int ACTIVE = 0;
int SINGLE_PARTICLE = 0;
int WHICH_PARTICLE = 0;
int SHOW_TABLE = 0;
double FRAME = 0.025;
double wleft,wright,wbottom,wtop;

int N;
int steps;
double rho;

obj *particle = NULL;
int **neighbour = NULL;

void savePPM()
{
    char filename[50];
    sprintf(filename, "softcore2d%d_%f.ppm", N, rho);
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
            printf("t = %f H = %f K = %f U = %f T = %f\n",steps*dt,H,K,U,T);
            savePPM();
            break;
        case ' ':
            ACTIVE = !ACTIVE;
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'q': case 'Q': case 27:
            destroy_table(neighbour,N);
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
            WHICH_PARTICLE = (WHICH_PARTICLE+1)%N;
            break;
        case GLUT_KEY_F3:
            SHOW_TABLE = !SHOW_TABLE;
            break;
        case GLUT_KEY_F11:
            glutFullScreenToggle();
            break;
        case GLUT_KEY_UP:
            dt *= 1.1;
            break;
        case GLUT_KEY_DOWN:
            dt /= 1.1;
            break;
        case GLUT_KEY_LEFT:
            rho /= 1.1;
            L = pow(N/rho, 1.0f/DIMENSION);
            init_pos(particle,N,0.5);
            compute_table(particle,neighbour,N);
            break;
        case GLUT_KEY_RIGHT:
            rho *= 1.1;
            L = pow(N/rho, 1.0f/DIMENSION);
            init_pos(particle,N,0.5);
            compute_table(particle,neighbour,N);
            break;
    }
}

void idle(void)
{
    if(ACTIVE){
        if(!(steps%10)) compute_table(particle,neighbour,N);
        integrate(particle,neighbour,N);
        reset_mom(particle,N,1.19/T);
        steps++;
    }
    glutPostRedisplay();
}

void initGL()
{
    wleft =  0.0 - FRAME;
    wright =  1.0 + FRAME;
    wbottom =  0.0 - FRAME;
    wtop =  1.0 + FRAME;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(wleft, wright, wbottom, wtop);
    glClearColor(1.0,1.0,1.0,0.0);
}
 
void reshape(int w, int h)
{
    WIDTH = w;
    HEIGHT = h;
    glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(WIDTH > HEIGHT){
        wleft = (0.0-FRAME) -(WIDTH-HEIGHT)*(1+2*FRAME)/(2*HEIGHT);
        wright = (1.0+FRAME)+(WIDTH-HEIGHT)*(1+2*FRAME)/(2*HEIGHT);
        wbottom = (0.0-FRAME);
        wtop = (1.0+FRAME);
    }else{
        wleft = (0.0-FRAME);
        wright = (1.0+FRAME);
        wbottom = (0.0-FRAME)-(HEIGHT-WIDTH)*(1+2*FRAME)/(2*WIDTH);
        wtop = (1.0+FRAME)+(HEIGHT-WIDTH)*(1+2*FRAME)/(2*WIDTH);
    }
    gluOrtho2D(wleft, wright, wbottom, wtop);
}

void drawCircle(double *pos, double radius, char *color)
{
    double i;
    glColor3ub(color[0],color[1],color[2]);
    /* first copy */
    glBegin(GL_POLYGON);
    for(i=0;i<2*PI;i+=PI/24)
        glVertex2f( (pos[0]+cos(i)*radius)/L, (pos[1]+sin(i)*radius)/L );
    glEnd();
    /* other copies */
    if((pos[0]+radius)/L>1){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L-1,(pos[1]+sin(i)*radius)/L);glEnd();}
    if((pos[0]-radius)/L<0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L+1,(pos[1]+sin(i)*radius)/L);glEnd();}
    if((pos[1]+radius)/L>1){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L,(pos[1]+sin(i)*radius)/L-1);glEnd();}
    if((pos[1]-radius)/L<0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L,(pos[1]+sin(i)*radius)/L+1);glEnd();}

    if( ((pos[0]+radius)/L>1)&&((pos[1]+radius)/L>1) )
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L-1,(pos[1]+sin(i)*radius)/L-1);glEnd();}
    if( ((pos[0]+radius)/L>1)&&((pos[1]-radius)/L<0) )
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L-1,(pos[1]+sin(i)*radius)/L+1);glEnd();}
    if( ((pos[0]-radius)/L<0)&&((pos[1]+radius)/L>1) )
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L+1,(pos[1]+sin(i)*radius)/L-1);glEnd();}
    if( ((pos[0]-radius)/L<0)&&((pos[1]-radius)/L<0) )
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L+1,(pos[1]+sin(i)*radius)/L+1);glEnd();}

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    char normal[3] = {33,102,172};
    char bright[3] = {127,205,187};
    char dark[3] = {8,29,88};
    char halo[3] = {237,248,177};
    char bighalo[3] = {255,255,217};

    int i;
    if(SINGLE_PARTICLE){
        drawCircle(particle[WHICH_PARTICLE].pos,rm,bighalo);
        drawCircle(particle[WHICH_PARTICLE].pos,rc,halo);
        if(SHOW_TABLE){
            for(i = 0; i < neighbour[WHICH_PARTICLE][0]; i++)
                drawCircle(particle[neighbour[WHICH_PARTICLE][i+1]].pos,0.5,bright);
        }else{
            for(i = 0; i < N; i++)
                drawCircle(particle[i].pos,0.5,bright);
        }
        drawCircle(particle[WHICH_PARTICLE].pos,0.5,dark);
    }else for(i = 0; i < N; i++) drawCircle(particle[i].pos,0.5,normal);

    /* draw window */
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
        glVertex2f(wleft,wbottom);
        glVertex2f(wright,wbottom);
        glVertex2f(wright,0.0);
        glVertex2f(wleft,0.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(wleft,1.0);
        glVertex2f(wright,1.0);
        glVertex2f(wright,wtop);
        glVertex2f(wleft,wtop);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(1.0,0.0);
        glVertex2f(wright,0.0);
        glVertex2f(wright,1.0);
        glVertex2f(1.0,1.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(wleft,0.0);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0,1.0);
        glVertex2f(wleft,1.0);
    glEnd();

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
    /* openGL settings */
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
    printf("%s\n%s\n\n",glGetString(GL_RENDERER),glGetString(GL_VERSION));

    /* MD settings */
    N = 100;
    rho = 0.5;
    L = pow(N/rho, 1.0f/DIMENSION);
    rc = 2.5;
    rm = rc + 0.3;
    dF = -24*(2/pow(rc,13)-1/pow(rc,7));
    Uc = 4*(1/(pow(rc,12))-1/(pow(rc,6)));
    steps = 0;
    dt = 0.001;

    obj alias[N];
    particle = alias;
    neighbour = create_table(neighbour,N);


    init_pos(particle,N,0.5);           /* square lattice        */
    init_mom(particle,N);               /* flat distribution     */
    reset_mom(particle,N,1.19/T);       /* set temperature       */
    compute_table(particle,neighbour,N);/* table of neighbours   */
    get_acc(particle,neighbour,N);      /* compute accelerations */

    printf("# N = %d rho = %f dt = %f\n\n",N,rho,dt);

    glutMainLoop();
    return 0;
}

