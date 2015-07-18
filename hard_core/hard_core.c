#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "hard_core.h"

void drawStat(){}

void showInfo()
{
    /* backup current model-view matrix */
    glPushMatrix();
    glLoadIdentity();

    /* set to 2D orthogonal projection */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    int h = height, dh = 18;
    drawString(1, h-=dh, "Particles: %d", n_particles);
    drawString(1, h-=dh, "Eta = %lf", ETA);
    drawString(1, h-=dh, "Sigma = %lf", SIGMA);
    drawString(1, h-=dh, "Temperature = %lf", temperature);
    drawString(1, h-=dh, "Runtime = %lf", runtime);
    drawString(1, h-=dh, "Pressure = %lf", pressure);
    drawString(1, h-=dh, "mfp = %lf pm %lf", mfp, dmfp);
    drawString(1, h-=dh, "Hits = %d", hits);

    /* restore projection matrix */
    glPopMatrix();

    /* restore modelview matrix */
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void drawStuff()
{
    int k;
    double red[3] = {1.0,0.2,0.2};
    double grey[3] = {0.2,0.2,0.2};
    for(k = 0; k < n_particles; k++){
        if((k==collider1)||(k==collider2))
            drawSphere(particle[k].pos, SIGMA/2, red);
        else
            drawSphere(particle[k].pos, SIGMA/2, grey);
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
            n_particles += 2;
            init();
            break;
        case 'N':
            if(n_particles >= 2) n_particles -= 2;
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
        case 'l': case 'L':
            get_mfp();
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

