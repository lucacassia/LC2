#include "ising.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

unsigned int active = 0;
void (*algorithm)() = MH;
float *pixels = NULL;
int zoom = 4;
unsigned char color[2][3] = {{237,248,177}, {44,127,184}};

void savePPM()
{
    char filename[50];
    sprintf(filename, "ising_%dx%d_%f.ppm", SIZE, SIZE, BETA);
    FILE *f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n255\n", zoom*SIZE, zoom*SIZE);
    int i,j,k,l;
    for(i = SIZE-1; i >= 0; i--)
        for( k = 0; k < zoom; k++)
            for(j = 0; j < SIZE; j++)
                for( l = 0; l < zoom; l++)
                    fwrite(color[(ising[CENTER].s+1)/2], sizeof(unsigned char), 3, f);
    fclose(f);
    printf("\nPPM file saved to %s\n",filename);
}

void GLInit()
{
    pixels = (float*)malloc(3 * zoom * SIZE * zoom * SIZE * sizeof(float));

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f ,0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, zoom*SIZE, 0.0, zoom*SIZE, 0.0, 1.0);
    init(SIZE,0);
}

void displayF()
{
    int i,j,k,l,t = 0;

    for(i = 0; i < SIZE; i++)
        for( k = 0; k < zoom; k++)
            for(j = 0; j < SIZE; j++)
                for( l = 0; l < zoom; l++){
                    pixels[t++] = color[(ising[CENTER].s+1)/2][0]/255.0f;
                    pixels[t++] = color[(ising[CENTER].s+1)/2][1]/255.0f;
                    pixels[t++] = color[(ising[CENTER].s+1)/2][2]/255.0f;
                }

    glRasterPos2i(0,0);
    glDrawPixels(zoom*SIZE, zoom*SIZE,GL_RGB,GL_FLOAT, pixels);
    glutSwapBuffers();
}

void idleF()
{
    if(active){ algorithm(); }
    glutPostRedisplay();
}

void keyboardF(unsigned char key, int mouseX, int mouseY)
{
    switch(key)
    {
        case 'q': case 'Q': case 27:
            clear();
            free(pixels);
            printf("\n[EXIT]\n");
            exit(EXIT_SUCCESS);
        case ' ':
            active =! active;
            if(active) printf("\n[ACTIVE]\n"); else printf("\n[PAUSED]\n");
            break;
        case '+':
            BETA += 0.01;
            printf("\n[BETA = %f]\n",BETA);
            break;
        case '-':
            BETA -= 0.01;
            printf("\n[BETA = %f]\n",BETA);
            break;
        case 'i': case 'I':
            init(SIZE,BETA);
            printf("\n[RESET]\n");
            break;
        case 'm': case 'M':
            if(algorithm == SW){
                algorithm = MH;
                printf("\n[Metropolis-Hasting]\n");
            }
            else{
                algorithm = SW;
                printf("\n[Swendsen-Wang]\n");
            }
            break;
        case 'p': case 'P':
            savePPM();
            break;
    }
}

int main(int argc, char *argv[])
{
    SIZE = 128;

    glutInit(&argc, argv);
    glutInitWindowSize(zoom*SIZE, zoom*SIZE); 
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutCreateWindow("ising"); 
    GLInit();
    glutDisplayFunc(displayF); 
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutMainLoop();
    return 0;
}

