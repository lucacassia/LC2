#ifndef ISING
#define ISING

#include <stdio.h>
#include <stdlib.h>
#include "mersenne.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include "cluster.h"

#define BETA_CRITICAL   (log(1+sqrt(2))/2)

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
    return (log( 1 + sqrt(2) ) / 2);
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

double get_correlation(int dist)
{
    double *Sx = (double*)malloc(size * sizeof(double));
    double *Sy = (double*)malloc(size * sizeof(double));
    int i,j;
    for(i = 0; i < size; i++)
        Sx[i] = Sy[i] = 0.0f;

    for(i = 0; i < size; i++) for(j = 0; j < size; j++){
        Sx[j] += ising[i][j].s;
        Sy[i] += ising[i][j].s;
    }
    for(i = 0; i < size; i++){
        Sx[i] /= size;
        Sy[i] /= size;
    }

    double correlation = 0.0f;
    for(i = 0; i < size; i++){
        correlation += Sx[i] * Sx[(i+dist)%size];
        correlation += Sx[i] * Sx[(size+i-dist)%size];
        correlation += Sy[i] * Sy[(i+dist)%size];
        correlation += Sy[i] * Sy[(size+i-dist)%size];
    }
    free(Sx);
    free(Sy);
    return correlation / (4 * size);
}

void dump_data(int lattice_size, double beta_value, void (*algorithm)(), int run_time)
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); }
    else{
        int id = (algorithm == SW);
        /* .bin header */
        char filename_bin[50];
        sprintf(filename_bin, "data/%d_%f_%s_%d.bin", lattice_size, beta_value, get_algorithm_string(algorithm), run_time);
        FILE *f_bin = fopen(filename_bin, "wb");
        int cols = 3+lattice_size/2;
        fwrite(&cols, sizeof(int), 1, f_bin);
        fwrite(&lattice_size, sizeof(int), 1, f_bin);
        fwrite(&beta_value, sizeof(double), 1, f_bin);
        fwrite(&id, sizeof(int), 1, f_bin);
        fwrite(&run_time, sizeof(int), 1, f_bin);
        /* data gathering */
        printf("\nExecuting %s : L = %d : β = %f : time = %d\n\n", get_algorithm_string(algorithm), lattice_size, beta_value, run_time);
        init(lattice_size, beta_value);
        printf("Gathering Data..."); fflush(stdout);
        double tmp; int t, dist;
        for(t = 0; t < run_time; t++){
            tmp = get_energy() / (lattice_size * lattice_size);
            fwrite(&tmp, sizeof(double), 1, f_bin);

            tmp = get_magnetization() / (lattice_size * lattice_size);
            fwrite(&tmp, sizeof(double), 1, f_bin);

            if(algorithm == MH){
                fwrite(&tmp, sizeof(double), 1, f_bin);
            }
            if(algorithm == SW){
                tmp = (get_largest_cluster() * 1.0f) / (lattice_size * lattice_size);
                fwrite(&tmp, sizeof(double), 1, f_bin);
            }
            for(dist = 0; dist < size / 2; dist++){
                tmp = get_correlation(dist);
                fwrite(&tmp, sizeof(double), 1, f_bin);
            }

            algorithm();
        }
        printf(" DONE!\n\n");
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

raw load_data(FILE *f, int column, int skip)
{
    fseek(f, 0L, SEEK_SET);
    raw content = { 0, 0.0f, 0, NULL, 0, NULL };
    int cols; fread(&cols, sizeof(int), 1, f );
    if(column < 0 || column > cols || skip < 0) return content;
    /* read lattice size */
    fread(&content.l, sizeof(int), 1, f);
    /* read beta value */
    fread(&content.b, sizeof(double), 1, f);
    /* read algorithm id and name */
    fread(&content.id, sizeof(int), 1, f);
    if(content.id == 0) content.algorithm = "MH";
    if(content.id == 1) content.algorithm = "SW";
    /* read size */
    fread(&content.size, sizeof(int), 1, f);
    /* skip initial data */
    fseek(f, cols * sizeof(double) * skip, SEEK_CUR);
    content.size -= skip;
    /* read data */
    content.data = (double*)malloc(content.size * sizeof(double));
    int t;
    for(t = 0; t < content.size; t++){
        fseek(f, column * sizeof(double), SEEK_CUR);
        fread(&content.data[t], sizeof(double), 1, f);
        fseek(f, ((cols-1)-column) * sizeof(double), SEEK_CUR);
    }
    fseek(f, 0L, SEEK_SET);
    return content;
}

typedef struct _header{
    int cols;           /* number of columns */
    int l;              /* lattice size */
    double b;           /* beta */
    int id;             /* algorithm id */
    char *algorithm;    /* algorithm name */
    int size;           /* number of samples */
}header;

header get_header(FILE *f)
{
    header hdr;
    fseek(f, 0L, SEEK_SET);
    /* read number of columns */
    fread(&hdr.cols, sizeof(int), 1, f );
    /* read lattice size */
    fread(&hdr.l, sizeof(int), 1, f);
    /* read beta value */
    fread(&hdr.b, sizeof(double), 1, f);
    /* read algorithm id and name */
    fread(&hdr.id, sizeof(int), 1, f);
    if(hdr.id == 0) hdr.algorithm = "MH";
    if(hdr.id == 1) hdr.algorithm = "SW";
    /* read size */
    fread(&hdr.size, sizeof(int), 1, f);
    return hdr;
}

double *bin_data(double *storage, int storage_size, int bin_size)
{
    if (storage_size < bin_size) return NULL;

    int n_bins = storage_size / bin_size;
    storage_size = bin_size * n_bins;

    double *binned_data = (double*)malloc(n_bins * sizeof(double));
    int t;
    for(t = 0; t < n_bins; t++)
        binned_data[t] = 0.0f;
    for(t = 0; t < storage_size; t++)
        binned_data[t/bin_size] += storage[t];
    for(t = 0; t < n_bins; t++)
        binned_data[t] /= bin_size;
    return binned_data;
}

double *jackknife(double *storage, int storage_size, int bin_size)
{
    if (storage_size < bin_size) return NULL;

    int n_bins = storage_size / bin_size;
    storage_size = bin_size * n_bins;

    int t;
    double sum = 0.0f;
    double *binned_data = (double*)malloc(n_bins * sizeof(double));
    for(t = 0; t < storage_size; t++)
        sum += storage[t];
    for(t = 0; t < n_bins; t++)
        binned_data[t] = 0.0f;
    for(t = 0; t < storage_size; t++)
        binned_data[t/bin_size] += storage[t];
    for(t = 0; t < n_bins; t++)
        binned_data[t] = (sum - binned_data[t]) / ( storage_size - bin_size );
    return binned_data;
}


#endif
