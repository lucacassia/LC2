#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "soft_core.h"

double *data = NULL;
int data_idx = 0;
int data_size = 1000;

double density = 0.5;
double temperature = 1.0;

void drawStat()
{
    int i;
    double dmax, dmin;
    dmax = dmin = data[0];
    for(i = 0; i < data_size; i++) {
    	if(data[i] > dmax)
            dmax = data[i];
    	if(data[i] < dmin)
            dmin = data[i];
    }

    glViewport( (GLsizei) WIDTH/20, (GLsizei) HEIGHT/20, (GLsizei) WIDTH*9/10, (GLsizei) HEIGHT/6);
    glScissor ( (GLsizei) WIDTH/20, (GLsizei) HEIGHT/20, (GLsizei) WIDTH*9/10, (GLsizei) HEIGHT/6);
    glEnable(GL_SCISSOR_TEST);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, dmin * 0.9, dmax * 1.1);

	glBegin(GL_LINE_STRIP);
    for(i = 1; i <= data_size; i++) {
    	glVertex2d( i / (float) (data_size-1) , data[(data_idx+i)%data_size]);
    }
	glEnd();

    glDisable(GL_SCISSOR_TEST);
}

void drawStuff()
{
    int k;
    double color[3] = {33,102,172};
    for(k = 0; k < n_particles; k++){
        drawSphere(particle[k].pos, SIGMA/box_size, color);
    }
}

void showInfo()
{
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    int h = HEIGHT, dh = 18;
    drawString(1, h-=dh, "n_particles: %d", n_particles);
    drawString(1, h-=dh, "box_size = %lf", box_size);
    drawString(1, h-=dh, "time_step = %.10e", time_step);
    drawString(1, h-=dh, "runtime = %e", runtime);
    drawString(1, h-=dh, "density = %lf", density);
    drawString(1, h-=dh, "T = %lf", get_temperature());


    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void keyboardF(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':
            ACTIVE = !ACTIVE;
            break;
        case '+':
            box_size *= 1.1;
            init(density,temperature);
            break;
        case '-':
            box_size /= 1.1;
            init(density,temperature);
            break;
        case 't':
            time_step /= 1.5;
            break;
        case 'T':
            time_step *= 1.5;
            break;
        case 'k':
            temperature /= 1.5;
            set_temperature(temperature);
            break;
        case 'K':
            temperature *= 1.5;
            set_temperature(temperature);
            break;
        case 'n':
            clear();
            n_particles += 2;
            init(density,temperature);
            break;
        case 'N':
            clear();
            if(n_particles > 1) n_particles -=2;
            init(density,temperature);
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'v': case 'V':
            v_angle = h_angle = 0;
            break;
        case 'r': case 'R':
            set_temperature(temperature);
            reset();
            break;
        case 'i': case 'I':
            init(density,temperature);
            break;
        case 'p': case 'P':
            print_pos();
            print_mom();
            break;
        case 'm': case 'M':
            MODE = !MODE;
            break;
        case 'q': case 'Q': case 27:
            clear();
            exit(0);
            break;
    }
}

void idleF(void)
{
    if(ACTIVE){
        data[data_idx] = run();
        data_idx = (data_idx+1)%data_size;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL - SoftCore3D");

    srand(time(NULL));
    glInit();
    init(0.5,1.0);

    glutDisplayFunc(displayF);
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutSpecialFunc(specialKeyboardF);
    glutReshapeFunc(reshapeF);

    glutMainLoop();
    return 0;
}

