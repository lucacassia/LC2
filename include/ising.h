#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include "mersenne.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include "cluster.h"

unsigned int size = 32;
spin **ising = NULL;
double beta = 0;

void clear()
{
    if(ising != NULL){
        int i; for(i = 0; i < size; i++){ if(ising[i] != NULL){ free(ising[i]); } }
        free(ising);
        ising = NULL;
    }
}

void init(double beta_value)
{
    int i,j,k;
    seed_mersenne( (long)time(NULL) );
    for(k = 0; k < 543210; k++) mersenne();

    clear();
    ising = (spin**)malloc(size * sizeof(spin*));
    for(i = 0; i < size; i++) ising[i] = (spin*)malloc(size * sizeof(spin));

    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        if( mersenne() < 0.5 ) ising[i][j].s = 1;
        else ising[i][j].s = -1;
    }

    beta = beta_value;
}

void MH()
{
    int new_spin;
    int i,j;
    double delta_energy;
    for(i = 0; i < size; i++) for(j = 0; j < size; j++) {
        if( mersenne() < 0.5 ) new_spin = 1; else new_spin = -1;
        delta_energy = -(ising[(i+1)%size][j].s+ising[(size+i-1)%size][j].s+ising[i][(j+1)%size].s+ising[i][(size+j-1)%size].s)*(new_spin-ising[i][j].s);
        if( delta_energy <= 0 || mersenne() < exp(- beta * delta_energy) ) ising[i][j].s = new_spin;
    }
}

void SW()
{
    int i,j,k,l;
    double prob = 1 - exp(- 2 * beta);
    for(i = 0; i < size; i++) for(j = 0; j < size; j++) {
        ising[i][j].l = ( ising[i][j].s == ising[i][(size+i-1)%size].s && mersenne() < prob );
        ising[i][j].u = ( ising[i][j].s == ising[(size+i-1)%size][j].s && mersenne() < prob );
        ising[i][j].cl = &ising[i][j];
    }

    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
    	if( ising[i][j].l &&  ising[i][j].u){
            ising[i][j].cl = cl_merge(ising[(size+i-1)%size][j].cl, ising[i][(size+j-1)%size].cl);
        }
        if(!ising[i][j].l &&  ising[i][j].u){
            ising[i][j].cl = ising[(size+i-1)%size][j].cl;
        }
        if( ising[i][j].l && !ising[i][j].u){
            ising[i][j].cl = ising[i][(size+j-1)%size].cl;
        }
    }
    for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        ising[i][j].cl = cl_find(ising[i][j].cl);

    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        if(ising[i][j].cl == &ising[i][j] && mersenne() < 0.5){
            spin *tmp = &ising[i][j];
            for(k = 0; k < size; k++) for(l = 0; l < size; l++){
                if(ising[k][l].cl == tmp) ising[k][l].s *= -1;
            }
        }
    }

}

double get_energy(){
    double energy = 0;
    int i,j; for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        energy += - ( ising[(size+i-1)%size][j].s + ising[i][(size+j-1)%size].s ) * ising[i][j].s;
    return energy;
}

double get_magnetization_nofabs(){
    double magnetization = 0;
    int i,j; for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        magnetization += ising[i][j].s;
    return magnetization;
}

double get_magnetization(){
    double magnetization = 0;
    int i,j; for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        magnetization += ising[i][j].s;
    return fabs(magnetization);
}

void run(void (*algorithm)())
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); }
    else{ algorithm(); }
}

void thermalize(void (*algorithm)())
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); }
    else{ int t; for(t = 0; t < 2000; t++){ algorithm(); } }
}

double get_moment(int n, double* storage, int storage_size)
{
    double tmp = 0; int i; for(i = 0; i < storage_size; i++) tmp += pow(storage[i], n);
    return tmp / storage_size;
}

char *get_algorithm_string(void (*algorithm)())
{
    if( algorithm == MH ) return "MH";
    if( algorithm == SW ) return "SW";
    return NULL;
}

int get_bin_size(void (*algorithm)())
{
    if( algorithm == MH ) return 200;
    if( algorithm == SW ) return 400;
    return NULL;
}

double * get_binned_data(void (*algorithm)(), double beta_value, int bin_number, double (*func)() )
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); return NULL; }
    printf("\nExecuting %s @ β = %f\n\n", get_algorithm_string(algorithm), beta_value); init(beta_value);
    printf("Thermalizing................"); fflush(stdout); thermalize(algorithm); printf("DONE!\n");

    double *storage = (double*)malloc(bin_number * sizeof(double));

    printf("Gathering Binned Data......."); fflush(stdout);
    int i, t, bin_size = get_bin_size(algorithm);
    double tmp;
    for(i = 0; i < bin_number; i++){
        tmp = 0.0f;
        for(t = 0; t < bin_size; t++){
            algorithm();
            tmp += func() / (size * size);
        }
        storage[i] = tmp / bin_size;
    }
    printf("DONE!\t%d Samples x %d Bin Gathered\n\n", bin_size, bin_number);
    clear();
    return storage;
}

double * get_data(void (*algorithm)(), double beta_value, int storage_size, double (*func)())
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); return NULL; }
    printf("\nExecuting %s @ β = %f\n\n", get_algorithm_string(algorithm), beta_value); init(beta_value);
    printf("Thermalizing................"); fflush(stdout); thermalize(algorithm); printf("DONE!\n");

    double *storage = (double*)malloc(storage_size * sizeof(double));

    printf("Gathering Data.............."); fflush(stdout);
    int t; for(t = 0; t < storage_size; t++){
        algorithm();
        storage[t] = func() / (size * size);
    }
    printf("DONE!\t%d Samples Gathered\n\n", storage_size);
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
