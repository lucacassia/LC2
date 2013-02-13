#include "ising.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#define SPIN_UP     1
#define SPIN_DOWN   0

int active = 0;
float *pixels = NULL;

void savePPM()
{
    unsigned char white[3] = {255,255,255};
    unsigned char black[3] = {0,0,0};

    FILE *f = fopen("image.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);
    int i,j;
    for(i = height-1; i >= 0; i--)
        for(j = 0; j < width; j++){
            if(ising[i*width+j].s == 1)
                fwrite(white, sizeof(unsigned char), 3, f);
            if(ising[i*width+j].s == -1)
                fwrite(black, sizeof(unsigned char), 3, f);
        }
    fclose(f);
}

void GLInit()
{
    pixels = (float*)malloc(3 * width * height * sizeof(float));

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
            pixels[k] = 1;
        else
            pixels[k] = 0;
    }

    glRasterPos2i(0,0);
    glDrawPixels(width, height, GL_LUMINANCE, GL_FLOAT, pixels);
    glutSwapBuffers();
}

void idleF()
{
    if(active){
        run();
    }
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
            beta +=0.01;
            break;
        case 'i': case 'I':
            init();
            break;
        case 'm': case 'M':
            mode = (mode+1)%3;
            break;
        case 'p': case 'P':
            savePPM();
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

