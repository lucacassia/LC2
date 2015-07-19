#ifndef HARDCORE2D
#define HARDCORE2D

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mersenne.h"
#include "vec2.h"

typedef struct body{
    double pos[DIMENSION];      /* position */
    double mom[DIMENSION];      /* momentum */
    double distance;            /* distance traveled */
    double last_collision_time; /* time of the last collision of the particle */
    int n_collisions;  /* collisions made */
}body;

body *particle = NULL;
double **collision_table = NULL;
body **history = NULL;
double **dtimes = NULL;
int *ptr = NULL;

double SIGMA;                   /* diameter of the disks */
double ETA;                     /* packing density */
int n_particles = 100;          /* number of particles */
int n_history = 100000;         /* number of time steps of the simulation */
double time_step = 0.0003f;

int collider[2];

double runtime;
double min_time;
double dp;
double mfp;
double dmfp;
int n_collisions;


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

void print_mom()
{
    char filename[64];
    sprintf(filename, "data/momentum_%d_%f.dat", n_particles, ETA);
    FILE *f = fopen(filename,"w");
    int i,j;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++)
            fprintf(f, "%e\t", particle[i].mom[j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

void print_distribution()
{
    int i;
    char filename[64];
    sprintf(filename, "data/distribution_%d_%f.dat", n_particles, ETA);
    FILE *f = fopen(filename,"w");
    for(i = 0; i < n_particles; i++)
        fprintf(f, "%e\n", module(particle[i].mom) );
    fclose(f);
}

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
    double energy = get_kinetic_energy();
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] *= sqrt(n_particles*temp/energy);
}


double get_min_time()
{
    int i,j;
    collider[0] = 0;
    collider[1] = 1;
    double minimum = collision_table[collider[0]][collider[1]];
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(collision_table[i][j] <= minimum){
                minimum = collision_table[i][j];
                collider[0] = i;
                collider[1] = j;
            }
    return minimum;
}

double get_collision_time(int i, int j)
{
    double dr[DIMENSION], dv[DIMENSION];
    double t, dx, dy, rr, rv, vv, delta, collision_time = DBL_MAX;

    for(dx = -1; dx <= 1 ; dx++){
        for(dy = -1; dy <= 1; dy++){
            dr[0] = dx + particle[j].pos[0] - particle[i].pos[0];
            dr[1] = dy + particle[j].pos[1] - particle[i].pos[1];

            dv[0] = particle[j].mom[0] - particle[i].mom[0];
            dv[1] = particle[j].mom[1] - particle[i].mom[1];

            rr = scalar(dr, dr);
            rv = scalar(dr, dv);
            vv = scalar(dv, dv);
            delta = rv*rv-vv*(rr-SIGMA*SIGMA);

            if((rv < 0)&&(delta > 0)){
                t = (-rv-sqrt(delta))/vv;
                if(t < collision_time)
                    collision_time = t;
                }
        }
    }
    return collision_time;
}

void get_collision_table()
{
    int i, j;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            collision_table[i][j] = get_collision_time(i,j);
}

void update_collision_table()
{
    int i, j;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(i == collider[0] || j == collider[0] || i == collider[1] || j == collider[1])
                collision_table[i][j] = get_collision_time(i,j);
            else
                collision_table[i][j] -= min_time;
}

void clear()
{
    int i;
    if(particle != NULL)
        free(particle);
    if(collision_table){
        for(i = 0; i < n_particles; i++)
            if(collision_table[i])
                free(collision_table[i]);
        free(collision_table);
    }
    if(history){
        for(i = 0; i < n_history; i++)
            if(history[i])
                free(history[i]);
        free(history);
    }
    if(dtimes){
        for(i = 0; i < n_history; i++)
            if(dtimes[i])
                free(dtimes[i]);
        free(dtimes);
    }
    if(ptr != NULL)
        free(ptr);
}

void reset()
{
    int i;
    for(i = 0; i < n_particles; i++){
        particle[i].distance = 0.0f;
        particle[i].last_collision_time = 0.0f;
        particle[i].n_collisions = 0;
    }

    runtime = 0;
    dp = 0;
    n_collisions = 0;
}

/* initialization */
int init(double eta, double temperature)
{
    ETA = eta;
    SIGMA = 1.1283791671 * sqrt( eta/n_particles );

    /* check if disks fit the box */
    int k = 0; while( k * k < n_particles ) k++;
    if( SIGMA > 1.0f / k ){
        printf("Disks are too close to each other!\n");
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
    collision_table = (double**)malloc( n_particles * sizeof(double*) );
    for(i = 0; i < n_particles; i++)
        collision_table[i] = (double*)malloc( n_particles * sizeof(double) );
    history = (body**)malloc( n_history * sizeof(body*) );
    for(i = 0; i < n_history; i++)
        history[i] = (body*)malloc( n_particles * sizeof(body) );
    dtimes = (double**)malloc( n_history * sizeof(double) );
    for(i = 0; i < n_history; i++)
        dtimes[i] = (double*)malloc( n_particles * sizeof(double) );
    ptr = (int*)malloc(n_particles*sizeof(int));

    /* initialize position and momentum of particles */
    for(i = 0; i < n_particles; i++){
        /* place disks on a square lattice */
        particle[i].pos[0] = (0.5f/k)+(i%k)*(1.0f/k);
        particle[i].pos[1] = (0.5f/k)+(i/k)*(1.0f/k);

        /* set random initial momentum in [-1:1] */
        particle[i].mom[0] = 2.0f * mersenne() - 1.0f;
        particle[i].mom[1] = 2.0f * mersenne() - 1.0f;
    }

    /* compute center of mass momentum */
    double com_momentum[DIMENSION] = {0.0f};
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)    
            com_momentum[j] += particle[i].mom[j];

    /* boost in the center of mass frame */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] -= com_momentum[j] / n_particles;

    set_temperature(temperature);

    /* init stuff */
    get_collision_table();
    get_min_time();
    reset();
    return 0;
}

void run()
{
    min_time = get_min_time();

    int k;
    for(k = 0; k < 2; k++){
        particle[collider[k]].distance += (runtime + min_time - particle[collider[k]].last_collision_time) * module(particle[collider[k]].mom);
        particle[collider[k]].last_collision_time = runtime + min_time;
        particle[collider[k]].n_collisions++;
    }

    double dr[DIMENSION], dv[DIMENSION], tmp[DIMENSION];

    for(k = 0; k < n_particles; k++){
        particle[k].pos[0] += particle[k].mom[0] * min_time;
        particle[k].pos[1] += particle[k].mom[1] * min_time;

        particle[k].pos[0] -= floor(particle[k].pos[0]);
        particle[k].pos[1] -= floor(particle[k].pos[1]);
    }

    dr[0] = particle[collider[1]].pos[0] - particle[collider[0]].pos[0];
    dr[1] = particle[collider[1]].pos[1] - particle[collider[0]].pos[1];

    double dx, dy, dz;
    for(dx = -1; dx <= 1 ; dx++){
        for(dy = -1; dy <= 1; dy++){
            for(dz = -1; dz <= 1; dz++){
                tmp[0] = dx + particle[collider[1]].pos[0] - particle[collider[0]].pos[0];
                tmp[1] = dy + particle[collider[1]].pos[1] - particle[collider[0]].pos[1];

                if(scalar(tmp,tmp) < scalar(dr,dr)){
                    for(k = 0; k < DIMENSION; k++)
                        dr[k] = tmp[k];
                }
            }
        }
    }

    dv[0] = particle[collider[0]].mom[0] - particle[collider[1]].mom[0];
    dv[1] = particle[collider[0]].mom[1] - particle[collider[1]].mom[1];

    tmp[0] = scalar(dv,dr)*dr[0]/scalar(dr,dr);
    tmp[1] = scalar(dv,dr)*dr[1]/scalar(dr,dr);

    particle[collider[0]].mom[0] -= tmp[0];
    particle[collider[0]].mom[1] -= tmp[1];

    particle[collider[1]].mom[0] += tmp[0];
    particle[collider[1]].mom[1] += tmp[1];

    update_collision_table();
/*
    history[ptr[collider[0]]][[collider[0]] = particle[collider[0]];
    history[ptr[collider[1]]][collider[1]] = particle[collider[1]];
    dtimes[ptr[collider[0]]][collider[0]] = runtime;
    dtimes[ptr[collider[1]]][collider[1]] = runtime;
    ptr[collider[0]] = (ptr[collider[0]]+1)%n_history;
    ptr[collider[1]] = (ptr[collider[1]]+1)%n_history;
*/
    n_collisions++;
    runtime += min_time;
    dp += module(dv);

}

double get_mean_free_path()
{
    int i;
    double tmp = 0.0f;
    for(i = 0; i < n_particles; i++)
        tmp += particle[i].distance / particle[i].n_collisions; 
    return tmp/n_particles;
}

void print()
{
    FILE *v = fopen("speed.dat","a");
    FILE *f = fopen("history.dat","a");
    FILE *t = fopen("times.dat","w");

    int i,k;
    for(k = 0; k < n_particles; k++){
        for(i = 0; i < n_history-1; i++){
            fprintf(t, "%e\n", dtimes[(ptr[k]+i+1)][k] - dtimes[(ptr[k]+i)][k]);
        }
    }

    for(k = 0; k < n_particles; k++){
        fprintf(v, "%e\t%e\n", particle[k].mom[0], particle[k].mom[1]);
    }

    fprintf(f, "%d\t%lf\t%lf\t%lf\t%e\n", n_particles, ETA, get_pressure(), get_temperature(), SIGMA*dp/(2*get_kinetic_energy()*runtime) );

    fclose(t);
    fclose(v);
    fclose(f);
}

#endif
