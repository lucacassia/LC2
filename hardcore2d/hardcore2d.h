#ifndef HARDCORE2D
#define HARDCORE2D

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "mersenne.h"
#include "vec2.h"

#define DEBUG

double SIGMA;                   /* diameter of the disks */
int n_particles = 100;          /* number of particles */
int n_history = 10000;          /* number of time steps of the simulation */
double time_step = 0.03f;

int n_collisions;
double runtime;
double dp;

int idx_history_time;
double time_prec;


typedef struct body{
    double pos[DIMENSION];      /* position */
    double mom[DIMENSION];      /* momentum */
    double distance;            /* distance traveled */
    double last_collision_time; /* time of the last collision of the particle */
    int n_collisions;  /* collisions made */
}body;

body *particle = NULL;      /* particle list */
body *history = NULL;       /* simulation history */
double *collision_table = NULL;   /* collision table */


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

/* rescale all the momenta to set the desired temperature */
void set_temperature(double temp)
{
    int i,j;
    double energy = get_kinetic_energy();
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] *= sqrt(n_particles*temp/energy);
}


/* compute collision time of the pair (i,j) */
double get_collision_time(int i, int j)
{
    double delta_pos[DIMENSION], delta_mom[DIMENSION];
    double t, rr, rv, vv, delta, collision_time = DBL_MAX;

    int k,dx[2];
    for(dx[0] = -1; dx[0] <= 1 ; dx[0]++)
        for(dx[1] = -1; dx[1] <= 1; dx[1]++){
            vv = rv = rr = 0.0f;
            for(k = 0; k < DIMENSION; k++){
                delta_pos[k] = (1.0f * dx[k]) + particle[j].pos[k] - particle[i].pos[k];
                delta_mom[k] = particle[j].mom[k] - particle[i].mom[k];
                rr += delta_pos[k] * delta_pos[k];
                rv += delta_pos[k] * delta_mom[k];
                vv += delta_mom[k] * delta_mom[k];
            }
            delta = rv*rv-vv*(rr-SIGMA*SIGMA);
            if( (rv < 0)&&(delta > 0) ){
                t = (-rv-sqrt(delta))/vv;
                if(t < collision_time)
                    collision_time = t;
            }
        }
    return collision_time;
}

/* fill collision table */
void get_collision_table()
{
    int i,j;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            collision_table[i*n_particles+j] = get_collision_time(i,j);
}

/* update collision table */
void update_collision_table(int collider1, int collider2)
{
    int i;
    for(i = 0; i < collider1; i++)
        collision_table[i*n_particles+collider1] = get_collision_time(i,collider1);
    for(i = 0; i < collider2; i++)
        collision_table[i*n_particles+collider2] = get_collision_time(i,collider2);
    int j;
    for(j = collider1+1; j < n_particles; i++)
        collision_table[collider1*n_particles+j] = get_collision_time(collider1,j);
    for(j = collider2+1; j < n_particles; j++)
        collision_table[collider2*n_particles+j] = get_collision_time(collider1,j);
}

/* save current state to history */
void save_to_history()
{
    if(idx_history_time < n_history){
        int j;
        for(j = 0; j < n_particles; j++)
            history[idx_history_time * n_particles + j] = particle[j];
        idx_history_time++;
    }else{ printf("\n *** history is full! ***\n"); }
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
void clean()
{
    if(particle)        free(particle);
    if(collision_table) free(collision_table);
    if(history)         free(history);
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
    clean();
    collision_table = (double*)malloc( n_particles * n_particles * sizeof(double) );
    particle = (body*)malloc( n_particles * sizeof(body));
    history = (body*)malloc( n_history * n_particles * sizeof(body) );

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

/* move particles for time dt */
void step(double dt){
    int i,j;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++){
            particle[i].pos[j] += particle[i].mom[j] * dt;
            particle[i].pos[j] -= floor(particle[i].pos[j]);
/*            particle[i].pos[j] = fmod(fmod( particle[i].pos[j]+particle[i].mom[j]*dt ,1.0)+1.0,1.0);*/
        }

        /* update all the table by subtracting dt */
        for(j = i+1; j < n_particles; j++)
            collision_table[i*n_particles+j] -= dt;
    }
    runtime += dt;
}

double run()
{
    /* find first pair (i,j) to collide */
    int i,j;
    int collider[2] = {0,1};
    double min_time = collision_table[1];
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(collision_table[i*n_particles+j] < min_time){
                min_time = collision_table[i*n_particles+j];
                collider[0] = i;
                collider[1] = j;
            }
#ifdef DEBUG
    printf("colliders = (%d,%d)\n",collider[0],collider[1]);
    printf("runtime + min_time = %e + %e = %e\n",runtime,min_time,runtime+min_time);
    printf("collision_table[%d*%d+%d] = %e\n",collider[0],n_particles,collider[1],collision_table[collider[0]*n_particles+collider[1]] );
#endif
    /* gather data at regular steps until first collision */
    while( idx_history_time * time_step < runtime + collision_table[collider[0]*n_particles+collider[1]] ){
        step( idx_history_time * time_step - runtime );
        save_to_history();
    }

    /* evolve until collision */
    step( collision_table[collider[0]*n_particles+collider[1]] );
#ifdef DEBUG
    printf("collision_table[%d*%d+%d] = %e\n",collider[0],n_particles,collider[1],collision_table[collider[0]*n_particles+collider[1]] );
#endif
    /* update data of colliding particles */
    for(i = 0; i < 2; i++){
        particle[collider[i]].distance += (runtime - particle[collider[i]].last_collision_time) * module(particle[collider[i]].mom);
        particle[collider[i]].last_collision_time = runtime;
        particle[collider[i]].n_collisions++;
#ifdef DEBUG
        printf("particle[%d].distance = %e\n",collider[i],particle[collider[i]].distance );
        printf("particle[%d].last_collision_time = %e\n",collider[i],particle[collider[i]].last_collision_time );
        printf("particle[%d].n_collisions = %d\n",collider[i],particle[collider[i]].n_collisions );
#endif
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

#ifdef DEBUG
    printf("n_collisions = %d\n", n_collisions );
    printf("runtime = %e\n", runtime );
#endif
    update_collision_table(collider[0], collider[1]);

    return min_time;
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
            tmp = get_dr2( &history[start * n_particles], &history[(start+shift)*n_particles] );
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

#endif
