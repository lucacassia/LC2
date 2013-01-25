#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "soft_core.h"

void drawStat()
{
    glEnable(GL_SCISSOR_TEST);
    glViewport(0, 0, (GLsizei) width , (GLsizei) height / 4); 
    glScissor (0, 0, (GLsizei) width , (GLsizei) height / 4); 
    glLoadIdentity();
    gluOrtho2D(0, 1, -dmax, dmax);
//    glClearColor(1,1,1,1);
	glColor3d(1,1,1);
	glBegin(GL_LINE_STRIP);
    int i;
    for(i = 0; i < NDATA; i++) {
    	glVertex2d( i / (float) (NDATA-1) , data[(ptr+i)%NDATA] / dmax);
    }
	glEnd();
    glDisable(GL_SCISSOR_TEST);

}

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
    drawString(1, h-=dh, "L = %lf", L);
    drawString(1, h-=dh, "dt = %.10e", dt);
    drawString(1, h-=dh, "Runtime = %e", runtime);
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
    int k;
    for(k = 0; k < N; k++){
        drawSphere(vec3_new(particle[k].r.x/L, particle[k].r.y/L, particle[k].r.z/L), 0.1/L, particle[k].c);
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
            L *= 1.1;
            init();
            break;
        case '-':
            L /= 1.1;
            init();
            break;
        case 't':
            dt /= 1.5;
            break;
        case 'T':
            dt *= 1.5;
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
            reset();
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

