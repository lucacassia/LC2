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
    unsigned int r, l, u, d;
}spin;

int mode = 1;

unsigned int width = 500;
unsigned int height = 500;
spin *ising = NULL;
unsigned int step;

long double J = 1;
long double beta = 0.1;
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
        deltaE = -J * ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * (new_spin - ising[CENTER].s) / 2;
        if( deltaE < 0 || mersenne() < exp(-beta*deltaE) ) ising[CENTER].s = new_spin;
    }
}

void SW()
{
    int i,j;
    double prob = 0.5;

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        if( ising[RIGHT].s == ising[CENTER].s && mersenne() < prob ){
            ising[RIGHT].l = ising[CENTER].r = 1;
        }else ising[RIGHT].l = ising[CENTER].r = 0;

        if( ising[LEFT].s == ising[CENTER].s && mersenne() < prob ){
            ising[LEFT].r = ising[CENTER].l = 1;
        }else ising[LEFT].r = ising[CENTER].l = 0;

        if( ising[UP].s == ising[CENTER].s && mersenne() < prob ){
            ising[UP].d = ising[CENTER].u = 1;
        }else ising[UP].d = ising[CENTER].u = 0;

        if( ising[DOWN].s == ising[CENTER].s && mersenne() < prob ){
            ising[DOWN].u = ising[CENTER].d = 1;
        }else ising[DOWN].u = ising[CENTER].d = 0;
    }

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[CENTER].done = 0;
        if(!ising[CENTER].done && ising[CENTER].l && ising[RIGHT].done){
            ising[CENTER].flip = ising[RIGHT].flip;
            ising[CENTER].done = 1;
        }
        if(!ising[CENTER].done && ising[CENTER].r && ising[LEFT].done){
            ising[CENTER].flip = ising[LEFT].flip;
            ising[CENTER].done = 1;
        }
        if(!ising[CENTER].done && ising[CENTER].u && ising[UP].done){
            ising[CENTER].flip = ising[UP].flip;
            ising[CENTER].done = 1;
        }
        if(!ising[CENTER].done && ising[CENTER].d && ising[DOWN].done){
            ising[CENTER].flip = ising[DOWN].flip;
            ising[CENTER].done = 1;
        }
        if(!ising[CENTER].done){
            ising[CENTER].flip = mersenne() < 0.5;
            ising[CENTER].done = 1;
        }
        if(ising[CENTER].flip) ising[CENTER].s = -ising[CENTER].s;
    }

}

void run()
{
    if(mode) metropolis();
    else SW();

    if(step%10 == 0){
        beta += 0.01;
        long double E;
        long long int M;
        int i,j;
        E = M = 0;
        for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
            E += -J * ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * ising[CENTER].s / 2;
            M += ising[CENTER].s;
        }
        mM += M;
        mE += E/(width*height);
        printf("\n<e> = %.10Le\t<M> = %.10Le\n",mE,10*mM/(width*height*step));
    }
    step++;
}

#endif
