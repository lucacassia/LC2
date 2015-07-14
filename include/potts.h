#ifndef POTTS
#define POTTS

#include <stdio.h>
#include <stdlib.h>
#include "mersenne.h"
#include <time.h>
#include <string.h>
#include <math.h>

#define BETA_CRITICAL   (log(1.0f+sqrt(3.0f)))

#define RIGHT  i][(j+1)%SIZE
#define LEFT   i][(SIZE+j-1)%SIZE
#define UP     (SIZE+i-1)%SIZE][j
#define DOWN   (i+1)%SIZE][j
#define CENTER i][j

int STATES = 3;
int SIZE = 32;
double BETA = 0.0f;

typedef struct _spin{
    int s;
    int link[4];
    int cl;
    struct _spin *next;
}spin;

spin **potts = NULL;
spin **cluster = NULL;

int merge_clusters(int a, int b)
{
    if(a != b){
        spin *tmp;
        for(tmp = cluster[b]; tmp->next != NULL; tmp = tmp->next)
            tmp->cl = a;
        tmp->cl = a;
        tmp->next = cluster[a];
        cluster[a] = cluster[b];
        cluster[b] = NULL;
    }
    return a;
}

void create_clusters()
{
    int i,j;
    /* activate links */
    for(i = 0; i < SIZE; i++) for(j = 0; j < SIZE; j++){
        potts[CENTER].link[0] = potts[RIGHT].link[2] = ( (potts[CENTER].s==potts[RIGHT].s)&&(mersenne()<(1-exp(-BETA))) );
        potts[CENTER].link[1] = potts[UP   ].link[3] = ( (potts[CENTER].s==potts[UP   ].s)&&(mersenne()<(1-exp(-BETA))) );
        potts[CENTER].link[2] = potts[LEFT ].link[0] = ( (potts[CENTER].s==potts[LEFT ].s)&&(mersenne()<(1-exp(-BETA))) );
        potts[CENTER].link[3] = potts[DOWN ].link[1] = ( (potts[CENTER].s==potts[DOWN ].s)&&(mersenne()<(1-exp(-BETA))) );
    }
    /* initialize every spin as its own cluster */
    for(i = 0; i < SIZE; i++) for(j = 0; j < SIZE; j++){
        potts[CENTER].cl = i*SIZE+j;
        cluster[potts[CENTER].cl] = &potts[CENTER];
        potts[CENTER].next = NULL;
    }
    /* merge linked clusters */
    for(i = 0; i < SIZE; i++) for(j = 0; j < SIZE; j++){
/*        if( potts[CENTER].link[0] ) merge_clusters(potts[CENTER].cl, potts[RIGHT].cl);*/
        if( potts[CENTER].link[1] ) merge_clusters(potts[CENTER].cl, potts[UP   ].cl);
        if( potts[CENTER].link[2] ) merge_clusters(potts[CENTER].cl, potts[LEFT ].cl);
/*        if( potts[CENTER].link[3] ) merge_clusters(potts[CENTER].cl, potts[DOWN ].cl);*/
    }
}

void SW()
{
    int k, new_spin;
    spin *tmp;
    /* flip clusters */
    for(k = 0; k < SIZE * SIZE; k++)
        if(cluster[k])
            if( cluster[k]->s != (new_spin = rand()%STATES) )
                for( tmp = cluster[k]; tmp != NULL; tmp = tmp->next )
                    tmp->s = new_spin;
    create_clusters();
}

void MH()
{
    int i, j, new_spin, delta_energy;
    for(i = 0; i < SIZE; i++) for(j = 0; j < SIZE; j++)
        if( potts[CENTER].s != (new_spin = rand()%STATES) ){
            delta_energy  = (potts[RIGHT].s == potts[CENTER].s) - (potts[RIGHT].s == new_spin);
            delta_energy += (potts[UP   ].s == potts[CENTER].s) - (potts[UP   ].s == new_spin);
            delta_energy += (potts[LEFT ].s == potts[CENTER].s) - (potts[LEFT ].s == new_spin);
            delta_energy += (potts[DOWN ].s == potts[CENTER].s) - (potts[DOWN ].s == new_spin);
            if( (delta_energy <= 0)||(mersenne() < exp(- BETA * delta_energy)) )
                potts[CENTER].s = new_spin;
        }
}

void clear()
{
    if(potts){
        int i;
        for(i = 0; i < SIZE; i++)
            if(potts[i])
                free(potts[i]);
        free(potts);
        potts = NULL;
    }
    if(cluster){
        free(cluster);
        cluster = NULL;
    }
}

void init(int lattice_size, double beta_value)
{
    SIZE = lattice_size;
    BETA = beta_value;

    int i,j,k;
    seed_mersenne( (long)time(NULL) );
    for(k = 0; k < 543210; k++) mersenne();
    srand(time(NULL));

    clear();
    cluster = (spin**)malloc(SIZE*SIZE*sizeof(spin*));
    potts = (spin**)malloc(SIZE * sizeof(spin*));
    for(i = 0; i < SIZE; i++){
        potts[i] = (spin*)malloc(SIZE * sizeof(spin));
        for(j = 0; j < SIZE; j++)
            potts[CENTER].s = 0;
    }

    create_clusters();
}

double get_beta_critical()
{
    return BETA_CRITICAL;
}

char *get_algorithm_string(void (*algorithm)())
{
    if( algorithm == MH ) return "MH";
    if( algorithm == SW ) return "SW";
    return NULL;
}

double get_energy()
{
    int i, j, energy = 0;
    for(i = 0; i < SIZE; i++) for(j = 0; j < SIZE; j++){
        energy -= (potts[UP].s == potts[CENTER].s) + (potts[LEFT].s == potts[CENTER].s);
    }
    return 1.0f * energy;
}

int get_magnetization(int p)
{
    int i, j;
    int magnetization = 0;
    for(i = 0; i < SIZE; i++) for(j = 0; j < SIZE; j++)
        if(potts[CENTER].s == p)
            magnetization++;
    return magnetization;
}

double RE(int p){ return cos(p*6.28318530718/STATES); }
double IM(int p){ return sin(p*6.28318530718/STATES); }

double get_magnetization_mod(double *frac)
{
    int p;
    double re = 0.0f;
    double im = 0.0f;
    for(p = 0; p < STATES; p++){
        re += RE(p)*frac[p];
        im += IM(p)*frac[p];
    }
    return sqrt(re*re+im*im);
}

int get_largest_cluster()
{
    int k;
    int cl_size, cl_size_max = 0;
    spin *tmp;
    for(k = 0; k < SIZE * SIZE; k++){
        cl_size = 0;
        for(tmp = cluster[k]; tmp != NULL; tmp = tmp->next)
            cl_size++;
        if(cl_size > cl_size_max)
            cl_size_max = cl_size;
    }
    return cl_size_max;
}

double get_correlation(int dist)
{
    double *Sxre = (double*)malloc(SIZE * sizeof(double));
    double *Sxim = (double*)malloc(SIZE * sizeof(double));
    double *Syre = (double*)malloc(SIZE * sizeof(double));
    double *Syim = (double*)malloc(SIZE * sizeof(double));
    int i,j;
    for(i = 0; i < SIZE; i++)
        Sxre[i] = Sxim[i] = Syre[i] = Syim[i] = 0.0f;

    for(i = 0; i < SIZE; i++) for(j = 0; j < SIZE; j++){
        Sxre[j] += RE(potts[i][j].s);
        Sxim[j] += IM(potts[i][j].s);
        Syre[i] += RE(potts[i][j].s);
        Syim[i] += IM(potts[i][j].s);
    }
    for(i = 0; i < SIZE; i++){
        Sxre[i] /= SIZE;
        Sxim[i] /= SIZE;
        Syre[i] /= SIZE;
        Syim[i] /= SIZE;
    }

    double correlation = 0.0f;
    for(i = 0; i < SIZE; i++){
        correlation += Sxre[i] * Sxre[(i+dist)%SIZE] + Sxim[i] * Sxim[(i+dist)%SIZE];
        correlation += Sxre[i] * Sxre[(SIZE+i-dist)%SIZE] + Sxim[i] * Sxim[(SIZE+i-dist)%SIZE];

        correlation += Syre[i] * Syre[(i+dist)%SIZE] + Syim[i] * Syim[(i+dist)%SIZE];
        correlation += Syre[i] * Syre[(SIZE+i-dist)%SIZE] + Syim[i] * Syim[(SIZE+i-dist)%SIZE];
    }
    free(Sxre);
    free(Sxim);
    free(Syre);
    free(Syim);
    return correlation / (4 * SIZE);
}

void dump_data(int lattice_size, double beta_value, void (*algorithm)(), int run_time)
{
    if( (algorithm != MH) && (algorithm != SW) ){ printf("\nInvalid Algorithm!\n"); }
    else{
        int id = (algorithm == SW);

        /* .bin header */
        char filename_bin[50];
        sprintf(filename_bin, "data/%d_%f_%s_%d.bin", lattice_size, beta_value, get_algorithm_string(algorithm), run_time);
        FILE *f_bin = fopen(filename_bin, "wb");
        int cols = 1 + STATES + 1 + lattice_size/2;

        fwrite(&cols, sizeof(int), 1, f_bin);
        fwrite(&STATES, sizeof(int), 1, f_bin);
        fwrite(&lattice_size, sizeof(int), 1, f_bin);
        fwrite(&beta_value, sizeof(double), 1, f_bin);
        fwrite(&id, sizeof(int), 1, f_bin);
        fwrite(&run_time, sizeof(int), 1, f_bin);

        /* data gathering */
        printf("Executing %s : q = %d : L = %d : time = %d : β = %f\n",get_algorithm_string(algorithm),STATES,lattice_size,run_time,beta_value);
        init(lattice_size, beta_value);

        int t, k;
        double tmp;
        double *frac = (double*)malloc( STATES * sizeof(double) );
        for(t = 0; t < run_time; t++){
            tmp = get_energy() / (lattice_size * lattice_size);
            fwrite(&tmp, sizeof(double), 1, f_bin);

            for(k = 0; k < STATES; k++)
                frac[k] = 1.0f * get_magnetization(k);
            fwrite(frac, sizeof(double), STATES, f_bin);

            tmp = get_magnetization_mod(frac) / (lattice_size * lattice_size);
            fwrite(&tmp, sizeof(double), 1, f_bin);

            for(k = 0; k < lattice_size / 2; k++){
                tmp = get_correlation(k);
                fwrite(&tmp, sizeof(double), 1, f_bin);
            }

            algorithm();
        }
        free(frac);
        fclose(f_bin);
        clear();
    }
}

typedef struct _header{
    int cols;           /* number of columns */
    int q;              /* number of states */
    int l;              /* lattice size */
    double b;           /* beta */
    int id;             /* algorithm id */
    char *algorithm;    /* algorithm name */
    int size;           /* number of samples */
}header;

typedef struct _raw{
    header hdr;         /* header containing infos */
    double *data;       /* samples */
}raw;

void raw_close(raw *obj)
{
    obj->hdr.cols = 0;
    obj->hdr.q = 0;
    obj->hdr.l = 0;
    obj->hdr.b = 0.0f;
    obj->hdr.id = 0;
    obj->hdr.algorithm = NULL;
    obj->hdr.size = 0;
    if(obj->data != NULL)
        free(obj->data);
    obj->data = NULL;
}

header get_header(FILE *f)
{
    header hdr;
    fseek(f, 0L, SEEK_SET);
    /* read number of columns */
    fread(&hdr.cols, sizeof(int), 1, f );
    /* read number of states */
    fread(&hdr.q, sizeof(int), 1, f);
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

raw load_data(FILE *f, int column, int skip)
{
    raw content;
    content.hdr = get_header(f);
    content.data = NULL;
    if((column >= 0)&&(column < content.hdr.cols)&&(skip >= 0)){
        /* skip initial data */
        fseek(f, content.hdr.cols * sizeof(double) * skip, SEEK_CUR);
        content.hdr.size -= skip;
        /* read data */
        content.data = (double*)malloc(content.hdr.size * sizeof(double));
        int t;
        for(t = 0; t < content.hdr.size; t++){
            fseek(f, column * sizeof(double), SEEK_CUR);
            fread(&content.data[t], sizeof(double), 1, f);
            fseek(f, ((content.hdr.cols-1)-column) * sizeof(double), SEEK_CUR);
        }
        /* set number of columns to 1 */
        content.hdr.cols = 1;
    }
    fseek(f, 0L, SEEK_SET);
    return content;
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

int get_bin_size(int ID, int lattice_size)
{
    if(ID == 0) return 1000;
    if(ID == 1) return 50;
    return 1;

}
#endif
