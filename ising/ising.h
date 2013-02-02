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

double J = 0.5;
double beta = 1e-8;
double Z,mM,mE;

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

double hamiltonian(int i, int j)
{
    return -J * ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s );
}

void metropolis()
{
    int i,j,new_spin;
    double deltaE;
    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        deltaE = -J * ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s );
        if( mersenne() < 0.5 ) new_spin = 1; else new_spin = -1;
        deltaE *= new_spin - ising[CENTER].s;
        if( mersenne() < exp(-deltaE) ) ising[CENTER].s = new_spin;
    }
}

void flip_cluster(spin *s, int flip)
{
    s->done = 1;
    if(flip) s->s = !s->s;

    if(s->u != NULL){
        s->u->d = NULL;
        flip_cluster(s->u,flip);
    }
    if(s->d != NULL){
        s->d->u = NULL;
        flip_cluster(s->d,flip);
    }
    if(s->l != NULL){
        s->l->r = NULL;
        flip_cluster(s->l,flip);
    }
    if(s->r != NULL){
        s->r->l = NULL;
        flip_cluster(s->r,flip);
    }
}

void SW()
{
    int i,j,k;
    for(k = 0; k < width*height; k++)
        ising[k].done = 0;

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[CENTER].done = 1;

        if( !ising[RIGHT].done ) {
            if( ising[RIGHT].s == ising[CENTER].s && mersenne() < 1-exp(beta*J) ){
                ising[CENTER].r = &ising[RIGHT];
                ising[RIGHT].l = &ising[CENTER];
            }
            else ising[RIGHT].l = ising[CENTER].r = NULL;
        }

        if( !ising[LEFT].done ) {
            if( ising[LEFT].s == ising[CENTER].s && mersenne() < 1-exp(beta*J) ){
                ising[CENTER].l = &ising[LEFT];
                ising[LEFT].r = &ising[CENTER];
            }
            else ising[LEFT].r = ising[CENTER].l = NULL;
        }

        if( !ising[DOWN].done ) {
            if( ising[DOWN].s == ising[CENTER].s && mersenne() < 1-exp(beta*J) ){
                ising[CENTER].d = &ising[DOWN];
                ising[DOWN].u = &ising[CENTER];
            }
            else ising[DOWN].u = ising[CENTER].d = NULL;
        }

        if( !ising[UP].done ) {
            if( ising[UP].s == ising[CENTER].s && mersenne() < 1-exp(beta*J) ){
                ising[CENTER].u = &ising[UP];
                ising[UP].d = &ising[CENTER];
            }
            else ising[UP].d = ising[CENTER].u = NULL;
        }
    }

    for(k = 0; k < width*height; k++)
        ising[k].done = 0;

    for(k = 0; k < width*height; k++) if(!ising[k].done)
        flip_cluster(&ising[k], (mersenne() < 0.5) );

}

void run()
{
    if(mode) metropolis();
    else     SW();

    if(step%10 == 0){
        double E, M;
        int k;
        for(M = E = k = 0; k < width*height; k++){
            E += hamiltonian(k/width, k%width);
            M += ising[k].s;
        }
        Z += exp(-beta*E);
        mM += M*exp(-beta*E);
        mE += E*exp(-beta*E);
//        printf("\n<e> = %.10e\t<M> = %.10e\n",mE/(Z*width*height),mM/(Z*width*height));
    }
    step++;
}

#endif
