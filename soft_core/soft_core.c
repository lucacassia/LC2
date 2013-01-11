#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "soft_core.h"

void drawStat()
{/*
    glViewport (0, 0, (GLsizei) width / 4, (GLsizei) height / 4); 
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-1,1,-dmax,dmax);
    glLoadIdentity();
    glClearColor(1,1,1,1);
	glColor3d(1,0,0);
	glBegin(GL_LINE_STRIP);
    int i;
    for(i = 0; i < NDATA; i++) {
    	glVertex2d(2.0 * ( i / (float) (NDATA-1) ) - 1.0, data[(ptr+i)%NDATA] / dmax);
    }
	glEnd();
    glutSwapBuffers();
*/}

void showInfo()
{
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);     // switch to projection matrix
    glPushMatrix();                  // save current projection matrix
    glLoadIdentity();                // reset projection matrix
    gluOrtho2D(0, width, 0, height);  // set to orthogonal projection

    int h = height, dh = 18;
    drawString(1, h-=dh, "Particles: %d", N);
    drawString(1, h-=dh, "Sigma = %lf", SIGMA);
    drawString(1, h-=dh, "dt = %lf", dt);
    drawString(1, h-=dh, "H = %lf", get_hamilton());
    drawString(1, h-=dh, "U = %lf", get_u());
    drawString(1, h-=dh, "T = %lf", get_temperature());

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}

void drawStuff()
{
    body *tmp = particles;
    while(tmp != NULL){
        drawSphere(tmp->r, SIGMA/2, tmp->c);
        tmp = tmp->next;
        if(tmp == particles) break;
    }
    showInfo();
}

void keyboardF(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':
            active = !active;
            break;
        case '+':
            dt *= 2;
            break;
        case '-':
            dt /= 2;
            break;
        case 'n':
            N += 2;
            init();
            break;
        case 'N':
            if(N > 1) N -=2;
            init();
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'v': case 'V':
            v_angle = h_angle = 0;
            break;
        case 'r': case 'R':

            break;
        case 'i': case 'I':
            init();
            break;
        case 'p': case 'P':
            print();
            break;
        case 'q': case 'Q': case 27:
            clear();
            exit(0);
            break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("soft core");

    srand(time(NULL));
    glInit();
    init();

    glutDisplayFunc(displayF);
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutSpecialFunc(specialKeyboardF);
    glutReshapeFunc(reshapeF);

    glutMainLoop();
    return 0;
}

