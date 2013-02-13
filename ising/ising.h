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
    unsigned int cl;
    unsigned int r, l, u, d;
}spin;

int mode = 1;

unsigned int width = 500;
unsigned int height = 500;
spin *ising = NULL;
unsigned int step,N;

long double beta = 0;
long double mM,mE;

double *CORR = NULL;

void clear()
{
    if(ising != NULL)
        free(ising);
    if(CORR != NULL)
        free(CORR);
}

void init()
{
    int k;
    seed_mersenne( (long)time(NULL) );
    for(k = 0; k < 543210; k++) mersenne();

    clear();
    ising = (spin*)malloc(width * height * sizeof(spin));
    CORR = (double*)malloc(height * sizeof(double));
    for(k = 0; k < width * height; k++)
        if( 1 ) ising[k].s = 1; else ising[k].s = -1;
    N = step = mM = mE = 0;
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

void heatbath()
{
    int i,j;
    long double E,prob;
    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        E = ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s );
        prob = 1 / (1 + exp(-2*beta*E));
        if( mersenne() < prob ) ising[CENTER].s = 1;
        else ising[CENTER].s = -1;
    }
}

void SW()
{
    int i,j;
    double prob = 1-exp(-2*beta);

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[RIGHT].l = ising[CENTER].r = ( ising[RIGHT].s == ising[CENTER].s && mersenne() < prob );
        //ising[LEFT ].r = ising[CENTER].l = ( ising[LEFT ].s == ising[CENTER].s && mersenne() < prob );
        //ising[UP   ].d = ising[CENTER].u = ( ising[UP   ].s == ising[CENTER].s && mersenne() < prob );
        ising[DOWN ].u = ising[CENTER].d = ( ising[DOWN ].s == ising[CENTER].s && mersenne() < prob );
        ising[CENTER].cl = 0;
    }

    cluster *tmp = NULL, *head = NULL;
    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        if(ising[CENTER].l && !ising[CENTER].cl && ising[LEFT].cl){
            ising[CENTER].cl = 1;
            tmp = cl_add_obj(cl_which(head,LEFT),CENTER);
        }
        if(ising[CENTER].r && !ising[CENTER].cl && ising[RIGHT].cl){
            ising[CENTER].cl = 1;
            tmp = cl_add_obj(cl_which(head,RIGHT),CENTER);
        }
        if(ising[CENTER].d && !ising[CENTER].cl && ising[DOWN].cl){
            ising[CENTER].cl = 1;
            tmp = cl_add_obj(cl_which(head,DOWN),CENTER);
        }
        if(ising[CENTER].u && !ising[CENTER].cl && ising[UP].cl){
            ising[CENTER].cl = 1;
            tmp = cl_add_obj(cl_which(head,UP),CENTER);
        }
        if(!ising[CENTER].cl){
            ising[CENTER].cl = 1;
            head = cl_add_cl(head,CENTER);
            tmp = cl_which(head,CENTER);
        }
        if(ising[CENTER].l){
            if(ising[LEFT].cl) tmp = cl_merge(tmp, cl_which(head,LEFT) );
            else{
                tmp = cl_add_obj(tmp,LEFT);
                ising[LEFT].cl = 1;
            }
        }
        if(ising[CENTER].r){
            if(ising[RIGHT].cl) tmp = cl_merge(tmp, cl_which(head,RIGHT) );
            else{
                tmp = cl_add_obj(tmp,RIGHT);
                ising[RIGHT].cl = 1;
            }
        }
        if(ising[CENTER].d){
            if(ising[DOWN].cl) tmp = cl_merge(tmp, cl_which(head,DOWN) );
            else{
                tmp = cl_add_obj(tmp,DOWN);
                ising[DOWN].cl = 1;
            }
        }
        if(ising[CENTER].u){
            if(ising[UP].cl) tmp = cl_merge(tmp, cl_which(head,UP) );
            else{
                tmp = cl_add_obj(tmp,UP);
                ising[UP].cl = 1;
            }
        }
    }

    unsigned int flip;
    cluster *k;
    tmp = head;
    while(tmp){
        flip = mersenne() < 0.5;
        if(flip) for(k = tmp; k != NULL; k = k->next_obj)
            ising[k->idx].s = -ising[k->idx].s;
        tmp = tmp->next_cl;
    }

    cl_clear(head);
}

void run()
{
    if(mode == 0) metropolis();
    if(mode == 1) heatbath();
    if(mode == 2) SW();

    if(step%10 == 0){
        long double E,M;
        int i,j;
        E = M = 0;
        for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
            E += - ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * ising[CENTER].s / 2;
            M += ising[CENTER].s;
        }
        N++;
        mM += abs(M);
        mE += abs(E);
        //printf("\nN = %d\te = %Lf\tM = %Lf\n",N,E/(width*height*N),mM/(width*height*N));
    }
    step++;
}

double correlation(int t){
    int i,j;
    double tmp1,tmp2,corr = 0;
    for(i = 0; i < height; i++){
        for(tmp1 = j = 0; j < width; j++) tmp1 += ising[i*width+j].s;
        for(tmp2 = j = 0; j < width; j++) tmp2 += ising[((i+t)%height)*width+j].s;
        corr += tmp1 * tmp2 / (width * width);
    }
    return corr / height;
}

#endif
