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

unsigned int width = 32;
unsigned int height = 32;
spin *ising = NULL;
double beta = 0;

void clear()
{
    if(ising != NULL) free(ising);
}

void init(double beta_value)
{
    seed_mersenne( (long)time(NULL) );
    int k; for(k = 0; k < 543210; k++) mersenne();

    clear();
    ising = (spin*)malloc(width * height * sizeof(spin));

    for(k = 0; k < width * height; k++)
        if( mersenne() < 0.5 ) ising[k].s = 1;
        else ising[k].s = -1;

    beta = beta_value;
}

void single_MH(int i, int j)
{
    int new_spin;
    double delta_energy;
    if( mersenne() < 0.5 ) new_spin = 1; else new_spin = -1;
    delta_energy = - ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * (new_spin - ising[CENTER].s);
    if( delta_energy < 0 || mersenne() < exp(- beta * delta_energy) ) ising[CENTER].s = new_spin;
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

void run(unsigned int algorithm_id)
{
    if( !algorithm_id ){ MH(); } else { SW(); }
}

void thermalize(unsigned int algorithm_id, unsigned int termalization_time)
{
    int k; for(k = 0; k < termalization_time; k++){ if ( !algorithm_id ) { MH(); } else { SW(); } }
}

double get_moment(int n, double* storage, int storage_size)
{
    double tmp = 0; int i; for(i = 0; i < storage_size; i++) tmp += pow(storage[i], n);
    return tmp / storage_size;
}

double * get_binned_data(int algorithm_id, double beta_value, int bin_size, int bin_number)
{
    init(beta_value);
    printf("\nExecuting %d @ β = %f\n\n", algorithm_id, beta_value);
    printf("Thermalizing..."); fflush(stdout);
    thermalize(algorithm_id, 500);
    printf("......DONE!\n");

    printf("Allocating Memory..."); fflush(stdout);
    double *storage = (double*)malloc(bin_number * sizeof(double));
    printf(".DONE!\t%d Bins\n", bin_number);

    printf("Gathering Binned Data..."); fflush(stdout);
    int t,i; double tmp;
    for(i = 0; i < bin_number; i++){
        tmp = 0.0f;
        for(t = 0; t < bin_size; t++){
            if ( !algorithm_id ) { single_MH( (t/width)%height, t%width); } else { SW(); }
            tmp += get_energy() / (height * width);
        }
        storage[t] = tmp / bin_size;
    }
    printf("....DONE!\t%d   Samples Gathered\n\n",storage_size);
    return storage;
}

double * get_data(int algorithm_id, double beta_value, int storage_size)
{
    init(beta_value);
    printf("\nExecuting %d @ β = %f\n\n", algorithm_id, beta_value);
    printf("Thermalizing..."); fflush(stdout);
    thermalize(algorithm_id, 500);
    printf("......DONE!\n");

    printf("Allocating Memory..."); fflush(stdout);
    double *storage = (double*)malloc(storage_size * sizeof(double));
    printf(".DONE!\t%d * sizeof(double)\n", storage_size);

    printf("Gathering Data..."); fflush(stdout);
    int t; for(t = 0; t < storage_size; t++){
        if ( !algorithm_id ) { single_MH( (t/width)%height, t%width); } else { SW(); }
        storage[t] = get_energy() / (height * width);
    }
    printf("....DONE!\t%d   Samples Gathered\n\n",storage_size);
    return storage;
}

double * bin_data(double *storage, int storage_size, int bin_size)
{
    if (storage_size < bin_size) return NULL;

    double *binned_data = (double*)malloc((storage_size/bin_size)*sizeof(double));
    return binned_data;
}

#endif
