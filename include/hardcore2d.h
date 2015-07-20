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
double ***buffer = NULL;
int idx;
int FULL_BUFFER_FLAG;

double SIGMA;                   /* diameter of the disks */
double ETA;                     /* packing density */
int n_particles = 100;          /* number of particles */
int buffer_size = 10000;        /* number of time steps of the simulation */
double time_step = 0.5f;

int collider[2];

double runtime;
double min_time;
double dp;
int n_collisions;


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
    int i,j;
    if(particle != NULL)
        free(particle);
    if(collision_table){
        for(i = 0; i < n_particles; i++)
            if(collision_table[i])
                free(collision_table[i]);
        free(collision_table);
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
    collision_table = NULL;
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
    n_collisions = 1;
    dp = 0;
    idx = 0;
    FULL_BUFFER_FLAG = 0;
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

    buffer = (double***)malloc( buffer_size * sizeof(double**) );
    for(i = 0; i < buffer_size; i++){
        buffer[i] = (double**)malloc( n_particles * sizeof(double*) );
        for(j = 0; j < n_particles; j++)
            buffer[i][j] = (double*)malloc( DIMENSION * sizeof(double) );
    }

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

double run()
{
    min_time = get_min_time();

    int i,j,k;

    if(!FULL_BUFFER_FLAG){
        while( idx * time_step < runtime + min_time){
            for(i = 0; i < n_particles; i++)
                for(j = 0; j < DIMENSION; j++){
                    buffer[idx][i][j] = particle[i].pos[j]+particle[i].mom[j] * ( idx * time_step - runtime );
                    buffer[idx][i][j] -= floor(buffer[idx][i][j]);
                }
            idx++;
            FULL_BUFFER_FLAG = !(idx < buffer_size);
        }
    }else FULL_BUFFER_FLAG = 1;


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

    n_collisions++;
    runtime += min_time;
    dp += module(dv);
    return min_time;
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

/* compute <dr²(dt)> by averaging on every particle at t,dt fixed. for each particle take the distance with its nearest copy */
double get_dr2(double **list0, double **list1)
{
    int i,j;
    int dx[DIMENSION];
    double distance, sum = 0.0f;
    double dr[DIMENSION];
    for(i = 0; i < n_particles; i++){
        /* first copy */
        for(j = 0; j < DIMENSION; j++)
            dr[j] = list1[i][j] - list0[i][j];
        distance = scalar(dr,dr);
        /* check other copies */
        for(dx[0] = -1; dx[0] <= 1 ; dx[0]++)
            for(dx[1] = -1; dx[1] <= 1; dx[1]++){
                for(j = 0; j < DIMENSION; j++)
                    dr[j] = dx[j] + list1[i][j] - list0[i][j];
                if(scalar(dr,dr) < distance)
                    distance = scalar(dr,dr);
            }
        sum += distance;
    }
    return sum / n_particles;
} 

/* compute <dr²(dt)> for every dt and write to file */
void print_dr2(char *filename)
{
    FILE *f = fopen(filename, "w");
    int count, start, shift;
    double tmp;
    double mean, error;
    for(shift = 0; shift < buffer_size; shift++){
        error = mean = count = 0.0f;
        for(start = 0; (start + shift) < buffer_size; start++){
            tmp = get_dr2( buffer[start], buffer[start+shift] );
            mean += tmp;
            error += tmp*tmp;
            count++;
        }
        mean /= count;
        error = sqrt( (error / count - mean * mean)/count );
        fprintf(f,"%e\t%e\t%e\n", shift * time_step, mean, error );
    }
    fclose(f);
}

#endif
