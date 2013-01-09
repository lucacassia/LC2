#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define SPIN_UP     255
#define SPIN_DOWN   0

int width = 300;
int height = 300;
char *pixels = NULL;

void clear()
{
    if(pixels != NULL)
        free(pixels);
}

void init()
{
    clear();
    srand(time(NULL));
    pixels = (char*)malloc(width * height * sizeof(char));
    int k;
    for(k = 0; k < width * height; k++)
        if(rand()%2)
            pixels[k] = SPIN_UP;
        else
            pixels[k] = SPIN_DOWN;
    k = 0;
}

int hamiltonian(int i, int j)
{
    int H = 0;
    if(pixels[i*width+(j+1)%width]) H++;
    else H--;
    if(pixels[i*width+(width+j-1)%width]) H++;
    else H--;
    if(pixels[((i+1)%height)*width+j]) H++;
    else H--;
    if(pixels[((height+i-1)%height)*width+j]) H++;
    else H--;
    return H/2.0;
}

void run()
{
    int k, old, tmp;
    for(k = 0; k < width*height; k++){
        old = -2*pixels[k]-1;
        tmp = 2*(rand()%2)-1;
        int deltaE = -hamiltonian(k/width, k%width) * (tmp - old);
        if(rand()*1.0/RAND_MAX < exp(-deltaE)){
            if(tmp == 1)
                pixels[k] = SPIN_UP;
            else
                pixels[k] = SPIN_DOWN;
        }
    }

}
#endif
