#include<GL/freeglut.h>

#define DIMENSION 2

#include "softcore.h"

#define PI 3.1415926535897932384626433832795
 
int WIDTH  = 600;
int HEIGHT = 600;
double FRAME = 0.025;
double wleft,wright,wbottom,wtop;
int ACTIVE = 0;
int SINGLE_PARTICLE = 0;
int WHICH_PARTICLE = 0;
int SHOW_TABLE = 0;

int steps;
double runtime;
double TEMP = 0.1;

obj *particle = NULL;
int **neighbour = NULL;
int **full_neighbour = NULL;

void initSC()
{
    /* MD settings */
    N = 1000;
    rho = 0.3;
    L = pow(N/rho, 1.0f/DIMENSION);
    steps = 0;
    runtime = 0;

    particle = (obj*)malloc(N*sizeof(obj));
    neighbour = create_table(neighbour);
    full_neighbour = create_table(full_neighbour);

    init_pos(particle,N,0.5);         /* square lattice        */
    init_mom(particle);               /* flat distribution     */
    reset_mom(particle,TEMP/T);       /* set temperature       */
    compute_table(particle,neighbour);/* table of neighbours   */
    compute_full_table(particle,full_neighbour);
    get_acc(particle,neighbour);      /* compute accelerations */


    printf("# N = %d rho = %f dt = %f\n\n",N,rho,dt);
}

void idle(void)
{
    if(ACTIVE){
        if(!(steps%10)){
            compute_table(particle,neighbour);
            compute_full_table(particle,full_neighbour);
        }
        integrate(particle,neighbour);
        steps++;
        runtime += dt;
    }
    glutPostRedisplay();
}

void savePPM()
{
    char filename[50];
    sprintf(filename, "softcore2d%d_%.2f_%.2f.4.ppm", N, rho, runtime);
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
        case '+':
            dt *= 1.1;
            break;
        case '-':
            dt /= 1.1;
            break;
        case 'T':
            TEMP *= 1.1;
            reset_mom(particle,TEMP/T); 
            break;
        case 't':
            TEMP /= 1.1;
            reset_mom(particle,TEMP/T); 
            break;
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
            destroy_table(neighbour);
            destroy_table(full_neighbour);
            free(particle);
            exit(0);
            break;
    }
}

void specialKeyboard(int key, int x, int y)
{
    int i; 
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
            for(i = 0; i < N; i++) particle[i].pos[1]=PBC(particle[i].pos[1]-L/100);
            break;
        case GLUT_KEY_DOWN:
            for(i = 0; i < N; i++) particle[i].pos[1]=PBC(particle[i].pos[1]+L/100);
            break;
        case GLUT_KEY_LEFT:
            for(i = 0; i < N; i++) particle[i].pos[0]=PBC(particle[i].pos[0]+L/100);
            break;
        case GLUT_KEY_RIGHT:
            for(i = 0; i < N; i++) particle[i].pos[0]=PBC(particle[i].pos[0]-L/100);
            break;
    }
}

void initGL()
{
    wleft   =  0.0 - FRAME;
    wright  =  1.0 + FRAME;
    wbottom =  0.0 - FRAME;
    wtop    =  1.0 + FRAME;

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
    /* original copy */
    glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L,(pos[1]+sin(i)*radius)/L);glEnd();
    /* copies overflowing at the edges */
    if((pos[0]+radius)/L>1){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L-1,(pos[1]+sin(i)*radius)/L);glEnd();}
    if((pos[0]-radius)/L<0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L+1,(pos[1]+sin(i)*radius)/L);glEnd();}
    if((pos[1]+radius)/L>1){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L,(pos[1]+sin(i)*radius)/L-1);glEnd();}
    if((pos[1]-radius)/L<0){glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L,(pos[1]+sin(i)*radius)/L+1);glEnd();}
    /* copies overflowing at the corners */
    if(((pos[0]+radius)/L>1)&&((pos[1]+radius)/L>1))
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L-1,(pos[1]+sin(i)*radius)/L-1);glEnd();}
    if(((pos[0]+radius)/L>1)&&((pos[1]-radius)/L<0))
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L-1,(pos[1]+sin(i)*radius)/L+1);glEnd();}
    if(((pos[0]-radius)/L<0)&&((pos[1]+radius)/L>1))
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L+1,(pos[1]+sin(i)*radius)/L-1);glEnd();}
    if(((pos[0]-radius)/L<0)&&((pos[1]-radius)/L<0))
        {glBegin(GL_POLYGON);for(i=0;i<2*PI;i+=PI/24)glVertex2f((pos[0]+cos(i)*radius)/L+1,(pos[1]+sin(i)*radius)/L+1);glEnd();}

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    char normal[3] = {33,102,172};
    char light[3] = {127,205,187};
    char bright[3] = {78,179,211};
    char halo[3] = {237,248,177};
    char bighalo[3] = {255,255,217};

    int i;
    if(SHOW_TABLE){
        drawCircle(particle[WHICH_PARTICLE].pos,rm,bighalo);
        drawCircle(particle[WHICH_PARTICLE].pos,rc,halo);
        for(i = 0; i < N; i++)
            drawCircle(particle[i].pos,0.5,light);
        for(i = 0; i < full_neighbour[WHICH_PARTICLE][0]; i++)
            drawCircle(particle[full_neighbour[WHICH_PARTICLE][i+1]].pos,0.5,bright);
        drawCircle(particle[WHICH_PARTICLE].pos,0.5,normal);
    }
    if(SINGLE_PARTICLE && !SHOW_TABLE)
        drawCircle(particle[WHICH_PARTICLE].pos,0.5,normal);
    if(!SINGLE_PARTICLE && !SHOW_TABLE)
        for(i = 0; i < N; i++)
            drawCircle(particle[i].pos,0.5,normal);

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

    initSC();

    glutMainLoop();
    return 0;
}

