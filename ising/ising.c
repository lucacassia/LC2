#include "ising.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#define SPIN_UP     1
#define SPIN_DOWN   0

int active = 0;
float *pixels = NULL;

void GLInit()
{
    pixels = (float*)malloc(width * height * sizeof(float));

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f ,0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, width, 0.0, height, 0.0, 1.0);
    init();
}

void displayF()
{
    int k;
    for(k = 0; k < width*height; k++){
        if(ising[k].s == 1)
            pixels[k] = SPIN_UP;
        else
            pixels[k] = SPIN_DOWN;
    }

    glRasterPos2i(0,0);
    glDrawPixels(width, height, GL_LUMINANCE, GL_FLOAT, pixels);
    glutSwapBuffers();
}

void idleF()
{
    if(active)
        run();
    glutPostRedisplay();
}

void keyboardF(unsigned char key, int mouseX, int mouseY)
{
    switch(key)
    {
        case 'q': case 'Q': case 27:
            clear();
            free(pixels);
            exit(EXIT_SUCCESS);
        case ' ':
            active =! active;
            break;
        case 'r': case 'R':
            Z = mE = mM = 0;
            break;
        case 'i': case 'I':
            init();
            break;
        case 'm': case 'M':
            mode = !mode;
            break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width, height); 
    glutInitDisplayMode( GLUT_LUMINANCE );
    glutCreateWindow("ising"); 
    GLInit();
    glutDisplayFunc(displayF); 
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutMainLoop();
    return 0;
}

