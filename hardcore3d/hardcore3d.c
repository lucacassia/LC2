#include <time.h>
#include <stdlib.h>

#include "scene.h"
#include "hardcore3d.h"

void drawStat(){}

void savePPM()
{
    char filename[50];
    sprintf(filename, "hardcore3d_%d_%f.ppm", n_particles, ETA);
    FILE *f = fopen(filename,"wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);
    unsigned char *snapshot = (unsigned char*)malloc(3*width*height*sizeof(unsigned char));
    glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,snapshot);
    fwrite(snapshot, sizeof(unsigned char), 3 * width * height, f);
    free(snapshot);
    fclose(f);
}

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
    drawString(1, h-=dh, "Runtime = %lf", runtime);
    drawString(1, h-=dh, "Collisions = %d", n_collisions);
    drawString(1, h-=dh, "Pressure = %lf", get_pressure());

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
        if((k==collider[0])||(k==collider[1]))
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
            init(ETA,1.0f);
            break;
        case '-':
            ETA /= 1.1;
            init(ETA,1.0f);
            break;
        case 'n':
            clear();
            n_particles += 2;
            init(ETA,1.0f);
            break;
        case 'N':
            clear();
            if(n_particles >= 2) n_particles -= 2;
            init(ETA,1.0f);
            break;
        case 'f': case 'F':
            glutFullScreenToggle();
            break;
        case 'v': case 'V':
            v_angle = h_angle = 0;
            break;
        case 'i': case 'I':
            init(ETA,1.0f);
            break;
        case 'p': case 'P':
            printf("Collisions: %d\t",n_collisions);
            printf("Runtime: %f\n",runtime);
            savePPM();
            break;
        case 'r': case 'R':
            reset();
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
    glutCreateWindow("OpenGL - HardCore3D");

    srand(time(NULL));
    glInit();
    init(0.5,1.0f);

    glutDisplayFunc(displayF);
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutSpecialFunc(specialKeyboardF);
    glutReshapeFunc(reshapeF);

    glutMainLoop();
    return 0;
}

