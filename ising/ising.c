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
    sprintf(filename, "ising_%dx%d_%f.ppm", SIZE, SIZE, BETA);
    FILE *f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n255\n", 4*SIZE, 4*SIZE);
    int i,j;
    for(i = SIZE-1; i >= 0; i--){
        for(j = 0; j < SIZE; j++){
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
        for(j = 0; j < SIZE; j++){
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
        for(j = 0; j < SIZE; j++){
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
        for(j = 0; j < SIZE; j++){
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
    pixels = (float*)malloc(3 * 4 * SIZE * 4 * SIZE * sizeof(float));

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f ,0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, 4*SIZE, 0.0, 4*SIZE, 0.0, 1.0);
    init(SIZE,0);
}

void displayF()
{
    int i,j,k; k = 0;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(ising[i][j].s == 1){ pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 1; k += 4; }
            else                  { pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 0; k += 4; }

        }
        for(j = 0; j < SIZE; j++){
            if(ising[i][j].s == 1){ pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 1; k += 4; }
            else                  { pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 0; k += 4; }

        }
        for(j = 0; j < SIZE; j++){
            if(ising[i][j].s == 1){ pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 1; k += 4; }
            else                  { pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 0; k += 4; }

        }
        for(j = 0; j < SIZE; j++){
            if(ising[i][j].s == 1){ pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 1; k += 4; }
            else                  { pixels[k] = pixels[k+1] = pixels[k+2] = pixels[k+3] = 0; k += 4; }

        }
    }

    glRasterPos2i(0,0);
    glDrawPixels(4*SIZE, 4*SIZE, GL_LUMINANCE, GL_FLOAT, pixels);
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
    glutInitWindowSize(4*SIZE, 4*SIZE); 
    glutInitDisplayMode( GLUT_LUMINANCE );
    glutCreateWindow("ising"); 
    GLInit();
    glutDisplayFunc(displayF); 
    glutIdleFunc(idleF);
    glutKeyboardFunc(keyboardF);
    glutMainLoop();
    return 0;
}

