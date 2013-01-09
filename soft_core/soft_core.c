#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "soft_core.h"

void drawStuff()
{
    body *tmp = particles;
    while(tmp != NULL){
        drawSphere(tmp->r, SIGMA/2, tmp->c);
        tmp = tmp->next;
        if(tmp == particles) break;
    }

    double h = 1.0, dh = 0.05;
    print_bitmap_string(0.0, h-=dh, 1.0, "Particles: %d", N);
    print_bitmap_string(0.0, h-=dh, 1.0, "Sigma = %lf", SIGMA);
    print_bitmap_string(0.0, h-=dh, 1.0, "dt = %lf", dt);
    print_bitmap_string(0.0, h-=dh, 1.0, "H = %lf", ham);
}

void keyboardF(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':
            active = !active;
            break;
        case 'h':
            ham = get_hamilton();
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
    glutInitWindowSize(500, 500);
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

