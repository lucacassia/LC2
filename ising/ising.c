#include "ising.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

int active = 0;

void savePPM(char *frame)
{
    FILE *f = fopen("ising.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);
    int i,j;
    for(i = height-1; i >= 0; i--)
        for(j = 0; j < width; j++){
            fwrite(&frame[(i*width+j)], sizeof(char), 1, f);
            fwrite(&frame[(i*width+j)], sizeof(char), 1, f);
            fwrite(&frame[(i*width+j)], sizeof(char), 1, f);
        }
    fclose(f);
}

void GLInit()
{
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f ,0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, width, 0.0, height, 0.0, 1.0);
    init();
}

void displayF()
{
    glRasterPos2i(0,0);
    glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
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
            exit(EXIT_SUCCESS);
        case ' ':
            active =! active;
            break;
        case 'p': case 'P':
            savePPM(pixels);
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

