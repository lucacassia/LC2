#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include "mersenne.h"
#include <time.h>
#include <string.h>
#include <math.h>

#define RIGHT  ( i*width+(j+1)%width )
#define LEFT   ( i*width+(width+j-1)%width )
#define UP     ( ((height+i-1)%height)*width+j )
#define DOWN   ( ((i+1)%height)*width+j )
#define CENTER ( i*width+j )

typedef struct _spin{
    int s;
    unsigned int done;
    unsigned int flip;
}spin;

int mode = 1;

unsigned int width = 500;
unsigned int height = 500;
spin *ising = NULL;
unsigned int step;

long double J = 1;
long double beta = 0.5;
long double Z,mM,mE;

void clear()
{
    if(ising != NULL)
        free(ising);
}

void init()
{
    int k;
    seed_mersenne( (long)time(NULL) );
    for(k = 0; k < 543210; k++) mersenne();

    clear();
    ising = (spin*)malloc(width * height * sizeof(spin));
    for(k = 0; k < width * height; k++)
        if(mersenne() < 0.5) ising[k].s = 1; else ising[k].s = -1;
    step = Z = mM = mE = 0;
}

void metropolis()
{
    int i,j,new_spin;
    long double deltaE;
    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        if( mersenne() < 0.5 ) new_spin = 1; else new_spin = -1;
        deltaE = -J * ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * (new_spin - ising[CENTER].s);
        if( deltaE < 0 || mersenne() < exp(-beta*deltaE) ) ising[CENTER].s = new_spin;
    }
}

void SW()
{
    int i,j,k;
    for(k = 0; k < width*height; k++){
        ising[k].done = 0;
        ising[k].flip = (mersenne() < 0.5);
    }

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[CENTER].done = 1;

        if( !ising[RIGHT].done ) {
            if( ising[RIGHT].s == ising[CENTER].s && mersenne() < 1-exp(-beta*J) ){
                ising[RIGHT].flip = ising[CENTER].flip;
            }
        }

        if( !ising[DOWN].done ) {
            if( ising[DOWN].s == ising[CENTER].s && mersenne() < 1-exp(-beta*J) ){
                ising[DOWN].flip = ising[CENTER].flip;
            }
        }
    }

    for(k = 0; k < width*height; k++) if(ising[k].flip)
        ising[k].s = -ising[k].s;

}

void run()
{
    if(mode) metropolis();
    else     SW();

    if(step%10 == 0){
        long double E;
        long long int M;
        int i,j;
        E = M = 0;
        for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
            E += -J * ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * ising[CENTER].s;
            M += ising[CENTER].s;
        }
        printf("M = %Ld\tB = %Le\n",M,E);
        Z += expl(-beta*E);
        mM += M*expl(-beta*E);
        mE += E*expl(-beta*E);
        //printf("\n<e> = %.10Le\t<M> = %.10Le\tZ = %.10Le\n",mE/(step*width*height),mM/(step*width*height),Z);
    }
    step++;
}

#endif
