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

int algorithm = 0;

unsigned int width = 100;
unsigned int height = 100;
spin *ising = NULL;
unsigned int markov_time;

double beta = 0;
double mean_energy;
double mean_magnetization;

double *correlation = NULL;
double *store_energy = NULL;
double *store_magnetization = NULL;
unsigned int store_ptr = 0;
unsigned int store_size = 1000;

void clear()
{
    if(ising != NULL) free(ising);
    if(correlation != NULL) free(correlation);
    if(store_energy != NULL) free(store_energy);
    if(store_magnetization != NULL) free(store_magnetization);
}

void init()
{
    seed_mersenne( (long)time(NULL) );
    int k; for(k = 0; k < 543210; k++) mersenne();

    clear();
    ising = (spin*)malloc(width * height * sizeof(spin));
    correlation = (double*)malloc(height * sizeof(double));
    store_energy = (double*)malloc(store_size * sizeof(double));
    store_magnetization = (double*)malloc(store_size * sizeof(double));

    for(k = 0; k < width * height; k++) if( 1 ) ising[k].s = 1; else ising[k].s = -1;

    markov_time = mean_magnetization = mean_energy = 0;
}

void MH()
{
    int i,j,new_spin;
    double delta_energy;
    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        if( mersenne() < 0.5 ) new_spin = 1; else new_spin = -1;
        delta_energy = - ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * (new_spin - ising[CENTER].s);
        if( delta_energy < 0 || mersenne() < exp(- beta * delta_energy) ) ising[CENTER].s = new_spin;
    }
}

void heatbath()
{
    int i,j;
    double energy,prob;
    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        energy = ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s );
        prob = 1 / (1 + exp(- 2 * beta * energy));
        if( mersenne() < prob ) ising[CENTER].s = 1;
        else ising[CENTER].s = -1;
    }
}

void SW()
{
    int i,j;
    double prob = 1 - exp(- 2 * beta);

    for(i = 0; i < height; i++) for(j = 0; j < width; j++) {
        ising[RIGHT].l = ising[CENTER].r = ( ising[RIGHT].s == ising[CENTER].s && mersenne() < prob );
        ising[LEFT ].r = ising[CENTER].l = ( ising[LEFT ].s == ising[CENTER].s && mersenne() < prob );
        ising[UP   ].d = ising[CENTER].u = ( ising[UP   ].s == ising[CENTER].s && mersenne() < prob );
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

double get_correlation(int t){
    int i,j;
    double tmp1, tmp2, corr = 0;
    for(i = 0; i < height; i++){
        for(tmp1 = j = 0; j < width; j++) tmp1 += ising[i*width+j].s;
        for(tmp2 = j = 0; j < width; j++) tmp2 += ising[((i+t)%height)*width+j].s;
        corr += tmp1 * tmp2 / (width * width);
    }
    return corr / height;
}

double get_energy(){
    double energy = 0;
    int i,j; for(i = 0; i < height; i++) for(j = 0; j < width; j++)
        energy += - ( ising[DOWN].s + ising[RIGHT].s ) * ising[CENTER].s;
    return energy;
}

double get_magnetization(){
    double magnetization = 0;
    int i,j; for(i = 0; i < height; i++) for(j = 0; j < width; j++)
        magnetization += ising[CENTER].s;
    return magnetization;
}

void run()
{
    if(algorithm == 0) MH();
    if(algorithm == 1) SW();

    int i; for(i = 0; i < height; i++) correlation[i] = get_correlation(i);
    mean_energy += store_energy[store_ptr] = abs( get_energy() );
    mean_magnetization += store_magnetization[store_ptr] = abs( get_magnetization() );
    store_ptr = (store_ptr + 1) % store_size;

    markov_time++;
}

double get_sigma(unsigned int m){
    double sigma, mean, tmp;
    int i,j;
    for(j = tmp = mean = sigma = i = 0; i < store_size; i++){
        tmp += store_energy[(store_ptr+i)%store_size];
        if((++j)%m == 0){
            sigma += tmp*tmp/(m*m);
            mean += tmp/m;
            tmp = 0;
        }
    }
    return sqrt((sigma-mean)/(store_size/m));
}

#endif
