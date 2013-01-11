#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "hard_core.h"

void drawStat(){}

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
    drawString(1, h-=dh, "Eta = %lf", ETA);
    drawString(1, h-=dh, "Sigma = %lf", SIGMA);
    drawString(1, h-=dh, "Temperature = %lf", temperature);
    drawString(1, h-=dh, "Runtime = %lf", runtime);
    drawString(1, h-=dh, "Pressure = %lf", pressure);
    drawString(1, h-=dh, "mfp = %lf", mfp/N/runtime);
    drawString(1, h-=dh, "Hits = %d", hits);

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
        if((k==collider1)||(k==collider2))
            drawSphere(particle[k].r, SIGMA/2, vec3_new(1.0,0.2,0.2));
        else
            drawSphere(particle[k].r, SIGMA/2, vec3_new(0.2,0.2,0.2));
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
            ETA *= 1.1;
            init();
            break;
        case '-':
            ETA /= 1.1;
            init();
            break;
        case 'n':
            N += 2;
            init();
            break;
        case 'N':
            if(N >= 2) N -= 2;
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
    glutInitWindowSize(500, 500);
    glutCreateWindow("hard core");

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

