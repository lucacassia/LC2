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
    struct _spin *u;
    struct _spin *d;
    struct _spin *l;
    struct _spin *r;
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

void flip_cluster(spin *local, int flip)
{
    local->done = 1;
    if(flip) local->s = !local->s;

    if(local->u != NULL){
        local->u->d = NULL;
        flip_cluster(local->u,flip);
    }
    if(local->d != NULL){
        local->d->u = NULL;
        flip_cluster(local->d,flip);
    }
    if(local->l != NULL){
        local->l->r = NULL;
        flip_cluster(local->l,flip);
    }
    if(local->r != NULL){
        local->r->l = NULL;
        flip_cluster(local->r,flip);
    }
}

void SW()
{
    int i,j,k;
    for(k = 0; k < width*height; k++){
        ising[k].done = 0;
        ising[k].r = ising[k].l = ising[k].u = ising[k].d = NULL;
    }

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[CENTER].done = 1;

        if( !ising[RIGHT].done ) {
            if( ising[RIGHT].s == ising[CENTER].s ){
                ising[CENTER].r = &ising[RIGHT];
                ising[RIGHT].l = &ising[CENTER];
            }
        }

        if( !ising[LEFT].done ) {
            if( ising[LEFT].s == ising[CENTER].s ){
                ising[CENTER].l = &ising[LEFT];
                ising[LEFT].r = &ising[CENTER];
            }
        }

        if( !ising[DOWN].done ) {
            if( ising[DOWN].s == ising[CENTER].s ){
                ising[CENTER].d = &ising[DOWN];
                ising[DOWN].u = &ising[CENTER];
            }
        }

        if( !ising[UP].done ) {
            if( ising[UP].s == ising[CENTER].s ){
                ising[CENTER].u = &ising[UP];
                ising[UP].d = &ising[CENTER];
            }
        }
    }

/*    for(k = 0; k < width*height; k++)
        ising[k].done = 0;

    for(k = 0; k < width*height; k++) if(!ising[k].done)
        flip_cluster(&ising[k], 1 );
*/

    flip_cluster(&ising[width*height/2],1);
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
