#include "ising.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#define SPIN_UP     1
#define SPIN_DOWN   0

unsigned int active = 0;
void (*algorithm)() = MH;
float *pixels = NULL;

void savePPM()
{
    unsigned char white[3] = {255,255,255};
    unsigned char black[3] = {0,0,0};
    char filename[50];
    sprintf(filename, "ising_%dx%d_%f.ppm", size, size, beta);
    FILE *f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n255\n", 4*size, 4*size);
    int i,j;
    for(i = size-1; i >= 0; i--){
        for(j = 0; j < size; j++){
            if(ising[i][j].s == 1){
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
            }
            if(ising[i][j].s == -1){
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
            }
        }
        for(j = 0; j < size; j++){
            if(ising[i][j].s == 1){
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
            }
            if(ising[i][j].s == -1){
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
            }
        }
        for(j = 0; j < size; j++){
            if(ising[i][j].s == 1){
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
            }
            if(ising[i][j].s == -1){
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
            }
        }
        for(j = 0; j < size; j++){
            if(ising[i][j].s == 1){
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
                fwrite(white, sizeof(unsigned char), 3, f);
            }
            if(ising[i][j].s == -1){
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
                fwrite(black, sizeof(unsigned char), 3, f);
            }
        }
    }
    fclose(f);
    printf("\nPPM file saved to %s\n",filename);
}

void GLInit()
{
    pixels = (float*)malloc(3 * size * size * sizeof(float));

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f ,0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, size, 0.0, size, 0.0, 1.0);
    init(0);
}

void displayF()
{
    int k;
    for(k = 0; k < size * size; k++){
        if(ising[k/size][k%size].s == 1)
            pixels[k] = 1;
        else
            pixels[k] = 0;
    }

    glRasterPos2i(0,0);
    glDrawPixels(size, size, GL_LUMINANCE, GL_FLOAT, pixels);
    glutSwapBuffers();
}

void idleF()
{
    if(active){ run(algorithm); }
    glutPostRedisplay();
}

void keyboardF(unsigned char key, int mouseX, int mouseY)
{
    switch(key)
    {
        case 'q': case 'Q': case 27:
            clear();
            free(pixels);
            printf("\nBye Bye!\n");
            exit(EXIT_SUCCESS);
        case ' ':
            active =! active;
            if(active) printf("\n[ACTIVE]\n"); else printf("\n[PAUSED]\n");
            break;
        case '+':
            beta += 0.01;
            printf("\nBeta: %f\n",beta);
            break;
        case '-':
            beta -= 0.01;
            printf("\nBeta: %f\n",beta);
            break;
        case 'i': case 'I':
            init(beta);
            printf("\nThe simulation has been reset!\n");
            break;
        case 'm': case 'M':
            if(algorithm == SW){
                algorithm = MH;
                printf("\nActivating Metropolis-Hasting Algorithm\n");
            }
            else{
                algorithm = SW;
                printf("\nActivating Swendsen–Wang Algorithm\n");
            }
            break;
        case 'p': case 'P':
            savePPM();
            break;
    }
}

int main(int argc, char *argv[])
{
    size = 100;

    glutInit(&argc, argv);
    glutInitWindowSize(size, size); 
    glutInitDisplayMode( GLUT_LUMINANCE );
    glutCreateWindow("ising"); 
    GLInit();
    glutDisplayFunc(displayF); 
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutMainLoop();
    return 0;
}

