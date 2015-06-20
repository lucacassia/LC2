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
unsigned int position;
double beta = 0;

void clear()
{
    if(ising != NULL){
        free(ising);
        ising = NULL;
    }
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
    position = 0;
}

void MH(unsigned int n)
{
    int new_spin;
    int i,j;
    double delta_energy;
    while(n){
        i = (position/width)%height;
        j = position%width;
        if( mersenne() < 0.5 ) new_spin = 1; else new_spin = -1;
        delta_energy = - ( ising[UP].s + ising[DOWN].s + ising[LEFT].s + ising[RIGHT].s ) * ( new_spin - ising[CENTER].s );
        if( delta_energy <= 0 || mersenne() < exp(- beta * delta_energy) ) ising[CENTER].s = new_spin;
        position = (position+1)%(width*height);
        n--;
    }
}
/*
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
*/
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

double get_magnetization_nofabs(){
    double magnetization = 0;
    int i,j; for(i = 0; i < height; i++) for(j = 0; j < width; j++)
        magnetization += ising[CENTER].s;
    return magnetization;
}

double get_magnetization(){
    double magnetization = 0;
    int i,j; for(i = 0; i < height; i++) for(j = 0; j < width; j++)
        magnetization += ising[CENTER].s;
    return fabs(magnetization);
}

void run(unsigned int algorithm_id)
{
    if( !algorithm_id ){ MH(width*height); } else { SW(); }
}

void thermalize(unsigned int algorithm_id)
{
    int k; for(k = 0; k < 1000; k++){ if ( !algorithm_id ) { MH(100*width*height); } else { SW(); } }
}

double get_moment(int n, double* storage, int storage_size)
{
    double tmp = 0; int i; for(i = 0; i < storage_size; i++) tmp += pow(storage[i], n);
    return tmp / storage_size;
}

double * get_binned_data(int algorithm_id, double beta_value, int bin_size, int bin_number, double (*func)() )
{
    init(beta_value);
    printf("\nExecuting %d @ β = %f\n\n", algorithm_id, beta_value);
    printf("Thermalizing................"); fflush(stdout);
    thermalize(algorithm_id);
    printf("DONE!\n");

    printf("Allocating Memory..........."); fflush(stdout);
    double *storage = (double*)malloc(bin_number * sizeof(double));
    printf("DONE!\t%d Bins\n", bin_number);

    printf("Gathering Binned Data......."); fflush(stdout);
    int t,i; double tmp;
    for(i = 0; i < bin_number; i++){
        tmp = 0.0f;
        for(t = 0; t < bin_size; t++){
            if ( !algorithm_id ) { MH(1); } else { SW(); }
            tmp += func() / (height * width);
        }
        storage[i] = tmp / bin_size;
    }
    printf("DONE!\t%d Samples Gathered\n\n",bin_number*bin_size);
    clear();
    return storage;
}

double * get_data(int algorithm_id, double beta_value, int storage_size, double (*func)())
{
    printf("\nExecuting %d @ β = %f\n\n", algorithm_id, beta_value); init(beta_value);
    printf("Thermalizing........."); fflush(stdout); thermalize(algorithm_id); printf("DONE!\n");

    double *storage = (double*)malloc(storage_size * sizeof(double));

    printf("Gathering Data......."); fflush(stdout);
    int t; for(t = 0; t < storage_size; t++){
        if ( !algorithm_id ) { MH(1); } else { SW(); }
        storage[t] = func() / (height * width);
    }
    printf("DONE!\t%d Samples Gathered\n\n",storage_size);
    clear();
    return storage;
}

double * bin_data(double *storage, int storage_size, int bin_size)
{
    if (storage_size < bin_size) return NULL;

    double *binned_data = (double*)malloc((storage_size/bin_size)*sizeof(double));
    int t;
    for(t = 0; t < storage_size/bin_size; t++)
        binned_data[t] = 0.0f;
    for(t = 0; t < bin_size*(storage_size/bin_size); t++)
        binned_data[t/bin_size] += storage[t];
    for(t = 0; t < storage_size/bin_size; t++)
        binned_data[t] /= bin_size;
    return binned_data;
}

#endif
