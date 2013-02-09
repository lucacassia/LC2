#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include "mersenne.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include "cluster.h"

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
unsigned int step,N;

long double beta = 0.7;
long double mM;

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
        if( 1 ) ising[k].s = 1; else ising[k].s = -1;
    N = step = mM = 0;
}

void metropolis()
{
    int i,j,new_spin;
    long double deltaE;
    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        if( mersenne() < 0.5 ) new_spin = 1; else new_spin = -1;
        deltaE = - ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * (new_spin - ising[CENTER].s);
        if( deltaE < 0 || mersenne() < exp(-beta*deltaE) ) ising[CENTER].s = new_spin;
    }
}

void SW()
{
    int i,j;
    double prob = 0.5;

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[RIGHT].l = ising[CENTER].r = ( ising[RIGHT].s == ising[CENTER].s && mersenne() < prob );
        ising[LEFT ].r = ising[CENTER].l = ( ising[LEFT ].s == ising[CENTER].s && mersenne() < prob );
        ising[UP   ].d = ising[CENTER].u = ( ising[UP   ].s == ising[CENTER].s && mersenne() < prob );
        ising[DOWN ].u = ising[CENTER].d = ( ising[DOWN ].s == ising[CENTER].s && mersenne() < prob );
    }

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[CENTER].done = 0;
        if( (!ising[CENTER].done) && ising[CENTER].r && ising[RIGHT].done){
            ising[CENTER].flip = ising[RIGHT].flip;
            ising[CENTER].done = 1;
        }
        if( (!ising[CENTER].done) && ising[CENTER].l && ising[LEFT].done){
            ising[CENTER].flip = ising[LEFT].flip;
            ising[CENTER].done = 1;
        }
        if( (!ising[CENTER].done) && ising[CENTER].u && ising[UP].done){
            ising[CENTER].flip = ising[UP].flip;
            ising[CENTER].done = 1;
        }
        if( (!ising[CENTER].done) && ising[CENTER].d && ising[DOWN].done){
            ising[CENTER].flip = ising[DOWN].flip;
            ising[CENTER].done = 1;
        }
        if( !ising[CENTER].done ){
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
        long double E,M;
        int i,j;
        E = M = 0;
        for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
            E += - ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * ising[CENTER].s / 2;
            M += ising[CENTER].s;
        }
        N++;
        mM += M;
        //printf("\nN = %d\te = %Lf\tM = %Lf\n",N,E/(width*height),mM/(width*height*N));
    }
    step++;
}

#endif
