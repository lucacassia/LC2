#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define SPIN_UP     1
#define SPIN_DOWN   0

double J = 1;
double beta = 1e-3;
int width = 300;
int height = 300;
int *spin = NULL;
float *pixels = NULL;

double Z,E;

void clear()
{
    if(pixels != NULL)
        free(pixels);
    if(spin != NULL)
        free(spin);
}

void init()
{
    clear();
    srand(time(NULL));
    pixels = (float*)malloc(width * height * sizeof(float));
    spin = (int*)malloc(width * height * sizeof(int));
    int k;
    for(k = 0; k < width * height; k++)
        if(rand()%2){
            spin[k] = 1;
            pixels[k] = SPIN_UP;
        }
        else{
            spin[k] = -1;
            pixels[k] = SPIN_DOWN;
        }
    Z = E = 0;
}

double hamiltonian(int i, int j)
{
    int H = 0;
    H += spin[i*width+(j+1)%width];
    H += spin[i*width+(width+j-1)%width];
    H += spin[((i+1)%height)*width+j];
    H += spin[((height+i-1)%height)*width+j];
    return -J*H;
}

void run()
{
    int k,new_spin;
    double deltaE;
    for(k = 0; k < width*height; k++){
        new_spin = 2*(rand()%2)-1;
        deltaE = hamiltonian(k/width, k%width) * (new_spin - spin[k]);
        if(rand()/(float)RAND_MAX < exp(-deltaE)){
            spin[k] = new_spin;
            if(spin[k] == 1)
                pixels[k] = SPIN_UP;
            else
                pixels[k] = SPIN_DOWN;
        }
    }
    double tmp = 0;
    for(k = 0; k < width*height; k++)
        tmp += hamiltonian(k/width, k%width);
    Z += exp(-beta*tmp);
    E += tmp*exp(-beta*tmp);
}

#endif
