#ifndef HARDCORE2D
#define HARDCORE2D

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include "mersenne.h"
#include "vec2.h"

/*#define DEBUG*/

double SIGMA;                   /* diameter of the disks */
int n_particles = 100;          /* number of particles */
int n_history = 100000;          /* number of time steps of the simulation */
double time_step = 0.0003f;

int n_collisions;
double runtime;
double dp;

int idx_history_time;

int collider[2];

typedef struct body{
    double pos[DIMENSION];      /* position */
    double mom[DIMENSION];      /* momentum */
    double distance;            /* distance traveled */
    double last_collision_time; /* time of the last collision of the particle */
    int n_collisions;  /* collisions made */
}body;

body *particle = NULL;              /* particle list */
body **history = NULL;              /* simulation history */
double **collision_table = NULL;    /* collision table */


void print_pos()
{
    FILE *f = fopen("data/position.dat","w");
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
    FILE *f = fopen("data/momentum.dat","w");
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
    FILE *f = fopen("data/boltzmann.dat","w");
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

double get_collision_time(int i, int j)
{
    double dr[DIMENSION], dv[DIMENSION];
    double t, dx[2], rr, rv, vv, delta, collision_time = DBL_MAX;

    for(dx[0] = -1; dx[0] <= 1 ; dx[0]++){
        for(dx[1] = -1; dx[1] <= 1; dx[1]++){
            sum(dr, dx, particle[j].pos);
            subtract(dr, particle[j].pos, particle[i].pos);
            subtract(dv, particle[j].mom, particle[i].mom);

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
    int i,j;
    double min = DBL_MAX;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++){
            collision_table[i][j] = get_collision_time(i,j);
            if( collision_table[i][j] < min ){
                collider[0] = i;
                collider[1] = j;
            }
        }
}

void save_to_history()
{
    if(idx_history_time < n_history){
        int j;
        for(j = 0; j < n_particles; j++)
            history[idx_history_time][j] = particle[j];
        idx_history_time++;
    }else{ printf("\n *** history is full! ***\n"); }
}

/* move particles for time dt */
void evolve(body *list, double dt){
    int i,j;
    for(i = 0; i < n_particles; i++)
        /* implement periodic boundary conditions */
        for(j = 0; j < DIMENSION; j++)
            list[i].pos[j] = fmod(fmod( list[i].pos[j]+particle[i].mom[j]*dt ,1.0)+1.0,1.0);
}

double collide()
{
    int i,j;
    double min_time = collision_table[collider[0]][collider[1]];

    /* gather data at regular steps until first collision */
/*
    while( idx_history_time * time_step < runtime + min_time ){
        save_to_history();
        evolve( history[idx_history_time-1], (idx_history_time-1) * time_step - runtime );
    }
*/
    /* evolve until collision */
    evolve( particle, min_time );

    /* update data of colliding particles */
    for(i = 0; i < 2; i++){
        particle[collider[i]].distance += (runtime + min_time - particle[collider[i]].last_collision_time) * module(particle[collider[i]].mom);
        particle[collider[i]].last_collision_time = runtime + min_time;
        particle[collider[i]].n_collisions++;
    }

    /* compute distance between colliding particles in the same box (not necessarily the shortest) */
    double dr[DIMENSION], dv[DIMENSION], tmp[DIMENSION];
    for(j = 0; j < DIMENSION; j++)
        dr[j] = particle[collider[1]].pos[j] - particle[collider[0]].pos[j];

    /* find the right copy of the particle to collide with */
    double dx[2];
    for(dx[0] = -1; dx[0] <= 1 ; dx[0]++)
        for(dx[1] = -1; dx[1] <= 1; dx[1]++){
            for(j = 0; j < DIMENSION; j++)
                tmp[j] = dx[j] + particle[collider[1]].pos[j] - particle[collider[0]].pos[j];
            if(scalar(tmp,tmp) < scalar(dr,dr))
                for(j = 0; j < DIMENSION; j++)
                    dr[j] = tmp[j];
        }

    /* update momenta of colliding particles */
    for(j = 0; j < DIMENSION; j++){
        dv[j] = particle[collider[0]].mom[j] - particle[collider[1]].mom[j];
        tmp[j] = scalar(dv,dr)*dr[j]/scalar(dr,dr);
        particle[collider[0]].mom[j] -= tmp[j];
        particle[collider[1]].mom[j] += tmp[j];
    }

    n_collisions++;
    dp += module(dv);
    runtime += min_time;

    get_collision_table();
    return min_time;
}

/* clear history but not the state */
void reset_variables()
{
    int i;
    for(i = 0; i < n_particles; i++){
        particle[i].distance = 0.0f;
        particle[i].last_collision_time = 0.0f;
        particle[i].n_collisions = 0;
    }

    idx_history_time = 0;
    n_collisions = 0;
    runtime = 0.0f;
    dp = 0.0f;

    get_collision_table();
    save_to_history();
}

/* free all the allocated memory */
void clear()
{
    int i;
    if(particle)
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
}

/* initialization */
int init(double eta, double temperature)
{
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
    particle = (body*)malloc( n_particles * sizeof(body));
    collision_table = (double**)malloc( n_particles * sizeof(double*) );
    for(i = 0; i < n_particles; i++)
        collision_table[i] = (double*)malloc( n_particles * sizeof(double) );
    history = (body**)malloc( n_history * sizeof(body*) );
    for(i = 0; i < n_history; i++)
        history[i] = (body*)malloc( n_particles * sizeof(body) );

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
    reset_variables();
    return 0;
}

/* compute <dr²(dt)> by averaging on every particle at dt fixed. for each particle take the distance with its nearest copy */
double get_dr2(body *list0, body *list1)
{
    int i,j;
    int dx[DIMENSION];
    double distance, sum = 0.0f;
    double dr[DIMENSION];
    for(i = 0; i < n_particles; i++){
        /* first copy */
        for(j = 0; j < DIMENSION; j++)
            dr[j] = list1[i].pos[j] - list0[i].pos[j];
        distance = scalar(dr,dr);
        /* check other copies */
        for(dx[0] = -1; dx[0] <= 1 ; dx[0]++)
            for(dx[1] = -1; dx[1] <= 1; dx[1]++){
                for(j = 0; j < DIMENSION; j++)
                    dr[j] = dx[j] + list1[i].pos[j] - list0[i].pos[j];
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
    for(shift = 0; shift < idx_history_time-1; shift++){
        error = mean = count = 0;
        for(start = 0; (start + shift) < idx_history_time; start++){
            tmp = get_dr2( history[start], history[start+shift] );
            mean += tmp;
            error += tmp*tmp;
            count++;
        }
        mean /= count;
        error = sqrt( error / count - mean * mean );
        fprintf(f,"%e\t%e\t%e\n", shift * time_step, mean, error );
    }
    fclose(f);
}

double get_mean_free_path()
{
    int i;
    double tmp = 0.0f;
    for(i = 0; i < n_particles; i++)
        tmp += particle[i].distance / particle[i].n_collisions; 
    return tmp/n_particles;
}

void update_collision_table(int collider1, int collider2)
{
    int i,j;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(i == collider1 || j == collider1 || i == collider2 || j == collider2)
                collision_table[i][j] = get_collision_time(i,j);
}

#endif
