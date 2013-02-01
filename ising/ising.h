#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define _rand() (rand()/(float)RAND_MAX)

typedef struct _spin{
    int s;
    unsigned int done;
    struct _spin *u;
    struct _spin *d;
    struct _spin *l;
    struct _spin *r;
}spin;

int mode = 1;

double J = 0.5;
double beta = 1e-3;
unsigned int width = 300;
unsigned int height = 300;
spin *ising = NULL;
unsigned int step;

double Z,mM,mE;

void clear()
{
    if(ising != NULL)
        free(ising);
}

void init()
{
    clear();
    srand(time(NULL));

    ising = (spin*)malloc(width * height * sizeof(spin));
    int k;
    for(k = 0; k < width * height; k++)
        if(0){
            ising[k].s = 1;
        }
        else{
            ising[k].s = -1;
        }
    step = Z = mM = mE = 0;
}

double hamiltonian(int i, int j)
{
    int H = 0;
    H += ising[i*width+(j+1)%width].s;
    H += ising[i*width+(width+j-1)%width].s;
    H += ising[((i+1)%height)*width+j].s;
    H += ising[((height+i-1)%height)*width+j].s;
    return -J*H;
}

void metropolis()
{
    int k,new_spin;
    double deltaE;
    for(k = 0; k < width*height; k++){
        new_spin = 2*(rand()%2)-1;
        deltaE = hamiltonian(k/width, k%width) * (new_spin - ising[k].s);
        if(rand()/(float)RAND_MAX < exp(-deltaE)){
            ising[k].s = new_spin;
        }
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
        ising[i*width+j].done = 1;

        k = i*width+(j+1)%width;
        if( !ising[k].done ) {
            if( ising[k].s == ising[i*width+j].s && _rand() < 1-exp(beta*J) ){
                ising[i*width+j].r = &ising[k];
                ising[k].l = &ising[i*width+j];
            }
            else ising[k].l = ising[i*width+j].r = NULL;
        }

        k = i*width+(width+j-1)%width;
        if( !ising[k].done ) {
            if( ising[k].s == ising[i*width+j].s && _rand() < 1-exp(beta*J) ){
                ising[i*width+j].l = &ising[k];
                ising[k].r = &ising[i*width+j];
            }
            else ising[k].r = ising[i*width+j].l = NULL;
        }

        k = ((i+1)%height)*width+j;
        if( !ising[k].done ) {
            if( ising[k].s == ising[i*width+j].s && _rand() < 1-exp(beta*J) ){
                ising[i*width+j].d = &ising[k];
                ising[k].u = &ising[i*width+j];
            }
            else ising[k].u = ising[i*width+j].d = NULL;
        }

        k = ((height+i-1)%height)*width+j;
        if( !ising[k].done ) {
            if( ising[k].s == ising[i*width+j].s && _rand() < 1-exp(beta*J) ){
                ising[i*width+j].u = &ising[k];
                ising[k].d = &ising[i*width+j];
            }
            else ising[k].d = ising[i*width+j].u = NULL;
        }
    }

    for(k = 0; k < width*height; k++)
        ising[k].done = 0;

    for(k = 0; k < width*height; k++) if(!ising[k].done) {
        flip_cluster(&ising[k], rand()%2);
    }

}

void run()
{
    if(mode)
        metropolis();
    else
        SW();

    if(step%10 == 0){
        double E, M; int k;
        for(M = E = k = 0; k < width*height; k++){
            E += hamiltonian(k/width, k%width);
            M += ising[k].s;
        }
        Z += exp(-beta*E);
        mM += M*exp(-beta*E);
        mE += E*exp(-beta*E);
        printf("\n<e> = %.10e\t<M> = %.10e\n",mE/(Z*width*height),mM/(Z*width*height));
    }
    step++;
}

#endif
