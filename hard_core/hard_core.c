#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "hard_core.h"

void drawStuff()
{
    int k;
    for(k = 0; k < N; k++){
        if((k==collider1)||(k==collider2))
            drawSphere(particle[k].r, SIGMA/2, vec3_new(1.0,0.2,0.2));
        else
            drawSphere(particle[k].r, SIGMA/2, vec3_new(0.2,0.2,0.2));
    }
    double h = 1.0, dh = 0.05;
    print_bitmap_string(0.0, h-=dh, 1.0, "Particles: %d", N);
    print_bitmap_string(0.0, h-=dh, 1.0, "Eta = %lf", ETA);
    print_bitmap_string(0.0, h-=dh, 1.0, "Sigma = %lf", SIGMA);
    print_bitmap_string(0.0, h-=dh, 1.0, "Temperature = %lf", temperature);
    print_bitmap_string(0.0, h-=dh, 1.0, "Runtime = %lf", runtime);
    print_bitmap_string(0.0, h-=dh, 1.0, "Pressure = %lf", pressure);
    print_bitmap_string(0.0, h-=dh, 1.0, "Hits = %d", hits);
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
            n++;
            init();
            break;
        case 'N':
            if(n > 0) n--;
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

