#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define SPIN_UP     1
#define SPIN_DOWN   0

double J = 0.5;
double beta = 1e-3;
unsigned int width = 300;
unsigned int height = 300;
int *spin = NULL;
float *pixels = NULL;
unsigned int step;

double Z,mM,mE;

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
    step = Z = mM = mE = 0;
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

void metropolis()
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
}

void SW()
{

}

void run()
{
    metropolis();
    if(step%10 == 0){
        int k;
        double E, M;
        for(M = E = k = 0; k < width*height; k++){
            E += hamiltonian(k/width, k%width);
            M += spin[k];
        }
        Z += exp(-beta*E);
        mM += M*exp(-beta*E);
        mE += E*exp(-beta*E);
        printf("\n<e> = %.10e\t<M> = %.10e\n",mE/(Z*width*height),mM/(Z*width*height));
    }
    step++;
}

#endif
