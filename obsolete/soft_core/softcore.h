#ifndef SOFTCORE
#define SOFTCORE

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vec.h"

typedef struct body{
    double pos[DIMENSION];      /* position */
    double unf[DIMENSION];      /* unfolded position */
    double mom[DIMENSION];      /* momentum */
    double acc[DIMENSION];      /* acceleration */
}body;

body *particle = NULL;          /* particle list */
int n_particles = 100;          /* number of particles */

double ***buffer = NULL;        /* history of the system */
int buffer_size = 10000;        /* size of the buffer */
int idx;                        /* buffer index counter */

int **neighbor = NULL;          /* neighbor of neighbors */

int FULL_BUFFER_FLAG;           /* flag that is set when buffer is full */
int UNFOLD_FLAG = 0;            /* flag to set unfolded coordinates calculations */

double runtime;                 /* time of the simulation */
double time_step;               /* time interval of the simulation */
double box_size;                /* size of the system */
int int_time;                   /* number of timesteps */

double RHO;                     /* density */
double R_C;                     /* cutoff radius */
double U_C;                     /* potential at the cutoff */
double F_C;                     /* force at the cutoff */
double H,K,U,T;                 /* energy, kinetic energy, potential and temperature */



int get_neighbor_entry(int i, int j);
void get_neighbor();
void set_position();
void run();
double get_MSD(double **list0, double **list1);

/* DIMENSION is set by #define at the beginning of the library */
/* WARNING: the definition of DIMENSION must precede the inclusion of softcore.h */

double get_total_momentum(){
    int i,j;
    double sum[DIMENSION] = {0.0f};
    for(i = 0; i < n_particles; i++)
        for (j = 0; j < DIMENSION; j++)
            sum[j] += particle[i].mom[j];
    return module(sum);
}

void set_temperature(double temp)
{
    int i,j;
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] *= sqrt(temp/T);
}

void clear()
{
    int i,j;
    if(particle != NULL)
        free(particle);
    if(neighbor){
        for(i = 0; i < n_particles; i++)
            if(neighbor[i])
                free(neighbor[i]);
        free(neighbor);
    }

    if(buffer){
        for(i = 0; i < buffer_size; i++)
            if(buffer[i]){
                for(j = 0; j < n_particles; j++)
                    if(buffer[i][j])
                        free(buffer[i][j]);
                free(buffer[i]);
            }
        free(buffer);
    }
    particle = NULL;
    neighbor = NULL;
    buffer = NULL;
}

void reset()
{
    idx = 0;
    runtime = 0;
    int_time = 0;
    FULL_BUFFER_FLAG = 0;
}

/* initialization */
int init(double num, double density, double temperature)
{
    R_C = 2.5;
    U_C =  4 * ( pow(1/R_C,12) - pow(1/R_C,6) );
    F_C = 24 * ( 2 * pow(1/R_C,13) - pow(1/R_C,7) );

    n_particles = num;
    RHO = density;
    box_size = cbrt(n_particles/RHO);

    /* allocate memory */
    clear();
    particle = (body*)malloc( n_particles * sizeof(body) );

    int i,j;
    neighbor = (int**)malloc( n_particles * sizeof(int*) );
    for(i = 0; i < n_particles; i++)
        neighbor[i] = (int*)malloc( n_particles * sizeof(int) );

    buffer = (double***)malloc( buffer_size * sizeof(double**) );
    for(i = 0; i < buffer_size; i++){
        buffer[i] = (double**)malloc( n_particles * sizeof(double*) );
        for(j = 0; j < n_particles; j++)
            buffer[i][j] = (double*)malloc( DIMENSION * sizeof(double) );
    }

    /* initialize position of particles */
    set_position();

    /* unfolding */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].unf[j] = particle[i].pos[j];

    /* initialize random generator */
    srand(time(NULL));

    /* compute center of mass momentum */
    double com_momentum[DIMENSION] = {0.0f};
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            /* set random initial momentum in [-1:1] */
            com_momentum[j] += particle[i].mom[j] = 2.0f * (rand()/(double)RAND_MAX) - 1.0f;

    /* boost in the center of mass frame */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] -= com_momentum[j] / n_particles;

    set_temperature(temperature);

    /* init other stuff */
    get_neighbor();
    reset();

    return 0;
}

void print_pos()
{
    char filename[64];
    sprintf(filename, "data/position_%d_%f.dat", n_particles, RHO);
    FILE *f = fopen(filename,"w");
    int i,j;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++)
            fprintf(f, "%e\t", particle[i].pos[j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

void print_single_pos(int i)
{
    char filename[64];
    sprintf(filename, "data/position_%d_%d_%f.dat", i, n_particles, RHO);
    FILE *f = fopen(filename,"a");
    int j;
    fprintf(f, "%e\t%e",RHO,runtime);
    for(j = 0; j < DIMENSION; j++)
        fprintf(f, "\t%e", particle[i].pos[j]);
    fprintf(f, "\n");
    fclose(f);
}

void print_mom()
{
    char filename[64];
    sprintf(filename, "data/momentum_%d_%.3f_%.3f.dat", n_particles, RHO, T);
    FILE *f = fopen(filename,"a");
    int i,j;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++)
            fprintf(f, "%e\t", particle[i].mom[j]);
        fprintf(f, "%e\n", module(particle[i].mom) );
    }
    fclose(f);
}

/* compute <dr²(dt)> for every dt and write to file */
void print_MSD(char *filename)
{
    FILE *f = fopen(filename, "w");
    int count, start, shift;
    double tmp;
    double mean, error;
    for(shift = 0; shift < buffer_size; shift++){
        error = mean = count = 0.0f;
        for(start = 0; (start + shift) < buffer_size; start++){
            tmp = get_MSD( buffer[start], buffer[start+shift] );
            mean += tmp;
            error += tmp*tmp;
            count++;
        }
        mean /= count;
        error = sqrt( (error / count - mean * mean)/count );
        fprintf(f,"%e\t%e\t%e\t%e\n", RHO, shift * time_step, mean, error );
    }
    fclose(f);
}

#endif
