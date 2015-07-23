#ifndef HARDCORE
#define HARDCORE

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mersenne.h"
#include "vec.h"

typedef struct body{
    double pos[DIMENSION];      /* position */
    double unf[DIMENSION];      /* unfolded position */
    double mom[DIMENSION];      /* momentum */
    double acc[DIMENSION];      /* acceleration */
    double distance;            /* distance traveled */
    double last_collision_time; /* time of the last collision */
    int n_collisions;           /* number of collisions made */
}body;

body *particle = NULL;          /* particle list */
int n_particles = 100;          /* number of particles */

double ***buffer = NULL;        /* history of the system */
int buffer_size = 10000;        /* size of the buffer */
int idx;                        /* buffer index counter */

double **table = NULL;          /* hard-core: collision table */
int **neighbors = NULL;         /* soft-core: neighbor table */

int FULL_BUFFER_FLAG;           /* flag that is set when buffer is full */
int UNFOLD_FLAG = 0;            /* flag to set unfolded coordinates calculations */

double SIGMA;                   /* diameter of the particles */
double ETA;                     /* packing density */

double time_step = 0.001f;      /* time interval of the simulation */
double box_size = 1.0f;         /* size of the system */
double runtime;                 /* time of the simulation */
int int_time;

int collider[2];
int n_collisions;
double min_time;
double dp;

/* these are the prototypes for the dimensional dependent functions     */
/* to be defined in the appropriate library: hardcore2d.h or hardcore3d */
double get_table_entry(int i, int j);
void get_table();
void update_table();
double get_params(double eta);
void get_other_data();
void set_position();
double get_MSD(double **list0, double **list1);
double run();

/* these are the d-independent functions */
/* DIMESION si set by #define at the beggining of the library */
/* WARNING: the definition of DIMENSION must precede the inclusion of hardcore.h */
double get_kinetic_energy()
{
    int i,j;
    double sum = 0.0f;
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            sum += particle[i].mom[j] * particle[i].mom[j];
    return sum / 2.0f;
}

double get_temperature()
{
    return (2.0f * get_kinetic_energy() / (DIMENSION * n_particles));
}

double get_pressure()
{
    return n_particles * get_temperature() * ( 1 + SIGMA * dp / ( 2 * get_kinetic_energy() * runtime ) );
}

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
    double old_temp = get_temperature();
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] *= sqrt(temp/old_temp);
}

double get_min_time()
{
    int i,j;
    collider[0] = 0;
    collider[1] = 1;
    double minimum = table[collider[0]][collider[1]];
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(table[i][j] <= minimum){
                minimum = table[i][j];
                collider[0] = i;
                collider[1] = j;
            }
    return minimum;
}


void clear()
{
    int i,j;
    if(particle != NULL)
        free(particle);
    if(table){
        for(i = 0; i < n_particles; i++)
            if(table[i])
                free(table[i]);
        free(table);
    }
    if(neighbors){
        for(i = 0; i < n_particles; i++)
            if(neighbors[i])
                free(neighbors[i]);
        free(neighbors);
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
    table = NULL;
    neighbors = NULL;
    buffer = NULL;
}

void reset()
{
    int i;
    for(i = 0; i < n_particles; i++){
        particle[i].distance = 0.0f;
        particle[i].n_collisions = 1;
        particle[i].last_collision_time = 0.0f;
    }

    runtime = 0;
    int_time = 0;
    n_collisions = 1;
    dp = 0;
    idx = 0;
    FULL_BUFFER_FLAG = 0;
}

/* initialization */
int init(double density, double temperature)
{
    if(get_params(density) == -1){
        printf("\nINIT ERROR!\n");
        return 1;
    }

    /* initialize pseudo-random number generators */
    int i,j;
    srand(time(NULL));
    seed_mersenne( (long)time(NULL) );
    for(i = 0; i < 543210; i++) mersenne();

    /* allocate memory */
    clear();
    particle = (body*)malloc( n_particles * sizeof(body) );

    table = (double**)malloc( n_particles * sizeof(double*) );
    for(i = 0; i < n_particles; i++)
        table[i] = (double*)malloc( n_particles * sizeof(double) );

    neighbors = (int**)malloc( n_particles * sizeof(int*) );
    for(i = 0; i < n_particles; i++)
        neighbors[i] = (int*)malloc( n_particles * sizeof(int) );

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

    /* compute center of mass momentum */
    double com_momentum[DIMENSION] = {0.0f};
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            /* set random initial momentum in [-1:1] */
            com_momentum[j] += particle[i].mom[j] = 2.0f * mersenne() - 1.0f;

    /* boost in the center of mass frame */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] -= com_momentum[j] / n_particles;

    set_temperature(temperature);

    /* init other stuff */
    get_table();
    reset();

    return 0;
}

double get_mean_free_path()
{
    int i;
    double tmp = 0.0f;
    for(i = 0; i < n_particles; i++)
        tmp += particle[i].distance / particle[i].n_collisions; 
    return tmp/n_particles;
}

double get_mean_collision_time()
{
    return n_particles * runtime / ( 2 * n_collisions );
}

void print_pos()
{
    char filename[64];
    sprintf(filename, "data/position_%d_%f.dat", n_particles, ETA);
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
    sprintf(filename, "data/position_%d_%d_%f.dat", i, n_particles, ETA);
    FILE *f = fopen(filename,"a");
    int j;
    fprintf(f, "%e\t%e",ETA,runtime);
    for(j = 0; j < DIMENSION; j++)
        fprintf(f, "\t%e", particle[i].pos[j]);
    fprintf(f, "\n");
    fclose(f);
}

void print_mom()
{
    char filename[64];
    sprintf(filename, "data/momentum_%d_%.3f_%.3f.dat", n_particles, ETA, get_temperature());
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
        fprintf(f,"%e\t%e\t%e\t%e\n", ETA, shift * time_step, mean, error );
    }
    fclose(f);
}

#endif
