#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include "mersenne.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include "cluster.h"

int size = 32;
double beta = 0.0f;
spin **ising = NULL;

void clear()
{
    if(ising != NULL){
        int i;
        for(i = 0; i < size; i++)
            if(ising[i] != NULL)
                free(ising[i]);
        free(ising);
        ising = NULL;
    }
}

void init(int lattice_size, double beta_value)
{
    size = lattice_size;
    beta = beta_value;

    int i,j,k;
    seed_mersenne( (long)time(NULL) );
    for(k = 0; k < 543210; k++) mersenne();

    clear();
    ising = (spin**)malloc(size * sizeof(spin*));
    for(i = 0; i < size; i++) ising[i] = (spin*)malloc(size * sizeof(spin));

    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        ising[i][j].s = 1;
        ising[i][j].cl = &ising[i][j];
    }
}

void MH()
{
    int new_spin;
    int i,j;
    double delta_energy;
    for(i = 0; i < size; i++) for(j = 0; j < size; j++) {
        if( mersenne() < 0.5f ) new_spin = 1; else new_spin = -1;
        delta_energy = -(ising[(i+1)%size][j].s+ising[(size+i-1)%size][j].s+ising[i][(j+1)%size].s+ising[i][(size+j-1)%size].s)*(new_spin-ising[i][j].s);
        if( delta_energy <= 0 || mersenne() < exp(- beta * delta_energy) ) ising[i][j].s = new_spin;
    }
}

void SW()
{
    int i,j;
    /* activate links */
    double prob = 1 - exp(- 2 * beta);
    for(i = 0; i < size; i++) for(j = 0; j < size; j++) {
        ising[i][j].l = ( ising[i][j].s == ising[i][(size+j-1)%size].s && mersenne() < prob );
        ising[i][j].u = ( ising[i][j].s == ising[(size+i-1)%size][j].s && mersenne() < prob );
        ising[i][j].cl = &ising[i][j];
    }
    /* create clusters */
    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
    	if( ising[i][j].l &&  ising[i][j].u){
            ising[i][j].cl = cl_merge( ising[(size+i-1)%size][j].cl, ising[i][(size+j-1)%size].cl );
        }
        if(!ising[i][j].l &&  ising[i][j].u){
            ising[i][j].cl = cl_find( ising[(size+i-1)%size][j].cl );
        }
        if( ising[i][j].l && !ising[i][j].u){
            ising[i][j].cl = cl_find( ising[i][(size+j-1)%size].cl );
        }
    }
    /* simplify clusters */
    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        ising[i][j].cl = cl_find(ising[i][j].cl);
    }
    /* flip clusters */
    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        ising[i][j].count = (ising[i][j].cl == &ising[i][j] && mersenne() < 0.5f);
    }
    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        if(ising[i][j].cl->count) ising[i][j].s = -ising[i][j].s;
    }
}

char *get_algorithm_string(void (*algorithm)())
{
    if( algorithm == MH ) return "MH";
    if( algorithm == SW ) return "SW";
    return NULL;
}

double get_beta_critical()
{
    return log( 1 + sqrt(2) ) / 2;
}

double get_energy()
{
    double energy = 0.0f;
    int i,j; for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        energy += - ( ising[(size+i-1)%size][j].s + ising[i][(size+j-1)%size].s ) * ising[i][j].s;
    return energy;
}

double get_magnetization_nofabs()
{
    double magnetization = 0.0f;
    int i,j; for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        magnetization += ising[i][j].s;
    return magnetization;
}

double get_magnetization()
{
    double magnetization = 0.0f;
    int i,j; for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        magnetization += ising[i][j].s;
    return fabs(magnetization);
}

int get_largest_cluster()
{
    int i,j;
    int cl_size_max = 0;
    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        ising[i][j].count = 0;
    }
    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        ising[i][j].cl->count++;
    }
    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        if(ising[i][j].count > cl_size_max){ cl_size_max = ising[i][j].count; }
    }
    return cl_size_max;
}

int get_cluster_number()
{
    int i,j;
    int n_clusters = 0;
    for(i = 0; i < size; i++) for(j = 0; j < size; j++)
        if(ising[i][j].cl == &ising[i][j])
            n_clusters++;
    return n_clusters;
}

void dump_data(int lattice_size, double beta_value, void (*algorithm)(), int run_time)
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); }
    else{
        int id = (algorithm == SW);
        /* .dat header */
        char filename_dat[50];
        sprintf(filename_dat, "data/%d_%f_%s_%d.dat", lattice_size, beta_value, get_algorithm_string(algorithm), run_time);
        FILE *f_dat = fopen(filename_dat, "w");
        fprintf(f_dat, "#\t%d\t%f\t%s\n", lattice_size, beta_value, get_algorithm_string(algorithm));
        /* .bin header */
        char filename_bin[50];
        sprintf(filename_bin, "data/%d_%f_%s_%d.bin", lattice_size, beta_value, get_algorithm_string(algorithm), run_time);
        FILE *f_bin = fopen(filename_bin, "wb");
        int cols = 4;
        fwrite(&cols, sizeof(int), 1, f_bin);
        fwrite(&lattice_size, sizeof(int), 1, f_bin);
        fwrite(&beta_value, sizeof(double), 1, f_bin);
        fwrite(&id, sizeof(int), 1, f_bin);
        fwrite(&run_time, sizeof(int), 1, f_bin);
        /* data gathering */
        printf("\nExecuting %s : L = %d : β = %f : time = %d\n\n", get_algorithm_string(algorithm), lattice_size, beta_value, run_time);
        init(lattice_size, beta_value);
        printf("Gathering Data..."); fflush(stdout);
        double tmp; int t;
        for(t = 0; t < run_time; t++){
            tmp = get_energy() / (lattice_size * lattice_size);
            fprintf(f_dat, "%f", tmp);
            fwrite(&tmp, sizeof(double), 1, f_bin);

            tmp = get_magnetization() / (lattice_size * lattice_size);
            fprintf(f_dat, "\t%f", tmp);
            fwrite(&tmp, sizeof(double), 1, f_bin);

            if(algorithm == MH){
                fprintf(f_dat, "\t%f", tmp);
                fwrite(&tmp, sizeof(double), 1, f_bin);
            }
            if(algorithm == SW){
                tmp = (get_largest_cluster() * 1.0f) / (lattice_size * lattice_size);
                fprintf(f_dat, "\t%f", tmp);
                fwrite(&tmp, sizeof(double), 1, f_bin);
            }

            fwrite(&tmp, sizeof(double), 1, f_bin); /* correlation (todo) */

            fprintf(f_dat, "\n");
            algorithm();
        }
        printf(" DONE!\n\n");
        fclose(f_dat);
        fclose(f_bin);
        clear();
    }
}

typedef struct _raw{
    int l;              /* lattice size */
    double b;           /* beta */
    int id;             /* algorithm id */
    char *algorithm;    /* algorithm name */
    int size;           /* number of samples */
    double *data;       /* samples */
}raw;

void raw_close(raw *obj)
{
    if(obj->data != NULL) free(obj->data);
    obj->l = 0;
    obj->b = 0.0f;
    obj->id = 0;
    obj->algorithm = NULL;
    obj->size = 0;
    obj->data = NULL;
}

raw load_data(FILE *f, int column)
{
    raw content = { 0, 0.0f, 0, NULL, 0, NULL };
    int cols; fread(&cols, sizeof(int), 1, f );
    if(column < 0 || column > cols) return content;
    /* read lattice size */
    fread(&content.l,sizeof(int),1,f);
    /* read beta value */
    fread(&content.b,sizeof(double),1,f);
    /* read algorithm ad and name */
    fread(&content.id,sizeof(int),1,f);
    if(content.id == 0) content.algorithm = "MH";
    if(content.id == 1) content.algorithm = "SW";
    /* read size */
    fread(&content.size,sizeof(int),1,f);
    /* read data */
    content.data = (double*)malloc(content.size * sizeof(double));
    int t;
    for(t = 0; t < content.size; t++){
        fseek(f,column*sizeof(double),SEEK_CUR);
        fread(&content.data[t],sizeof(double),1,f);
        fseek(f,((cols-1)-column)*sizeof(double),SEEK_CUR);
    }
    fseek(f, 0L, SEEK_SET);
    return content;
}

/*
int thermalization_time = 1000;

void thermalize(void (*algorithm)())
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); }
    else{ int t; for(t = 0; t < thermalization_time; t++){ algorithm(); } }
}

int get_bin_size(void (*algorithm)())
{
    if( algorithm == MH ) return 1000;
    if( algorithm == SW ) return 50;
    return NULL;
}

double **get_binned_data(void (*algorithm)(), double beta_value, int bin_number)
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); return NULL; }
    printf("\nExecuting %s @ β = %f\n\n", get_algorithm_string(algorithm), beta_value); init(beta_value);
    printf("Thermalizing................"); fflush(stdout); thermalize(algorithm); printf("DONE!\n");

    double **storage = (double**)malloc(2 * sizeof(double*));
    storage[0] = (double*)malloc(bin_number * sizeof(double));
    storage[1] = (double*)malloc(bin_number * sizeof(double));

    printf("Gathering Binned Data......."); fflush(stdout);
    int i, t, bin_size = get_bin_size(algorithm);
    double tmp[2];
    for(i = 0; i < bin_number; i++){
        tmp[0] = tmp[1] = 0.0f;
        for(t = 0; t < bin_size; t++){
            algorithm();
            tmp[0] += get_energy() / (size * size);
            if(algorithm == MH){ tmp[1] += get_magnetization() / (size * size); }
            if(algorithm == SW){ tmp[1] += get_largest_cluster() / (size * size); }
        }
        storage[0][i] = tmp[0] / bin_size;
        storage[1][i] = tmp[1] / bin_size;
    }
    printf("DONE!\t%d Samples x %d Bin Gathered\n\n", bin_size, bin_number);
    clear();
    return storage;
}

double *get_data(void (*algorithm)(), double beta_value, int storage_size, double (*func)())
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

double *bin_data(double *storage, int storage_size, int bin_size)
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
*/
#endif
