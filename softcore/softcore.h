#ifndef SOFTCORE
#define SOFTCORE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct body{
    double  pos[DIMENSION];  /* position */
    double  mom[DIMENSION];  /* momentum */
    double  acc[DIMENSION];  /* acceleration */
}body;

int **table = NULL; /* neighbors table */

double Rc = 2.5;    /* cutoff radius */
double Uc;          /* potential at the cutoff */
double Fc;          /* force at the cutoff */

int n_particles;    /* number of particles */
double rho;         /* density */
double L;           /* box size */
double time_step;
double runtime;
double thermalization_time;
double H,K,U,T;


void clear(body *particle)
{
    if(particle)
        free(particle);
    particle = NULL;

    if(table){
        int i;
        for(i = 0; i < n_particles; i++)
            if(table[i])
                free(table[i]);
        free(table);
    }table = NULL;
}

double potential(double r)
{
    if(r > Rc) return 0;
    return 4 * ( pow(1/r,12) - pow(1/r,6) ) - Uc + Fc * (r - Rc);
}

double force(double r)
{
    return 24 * ( 2 * pow(1/r,13) - pow(1/r,7) ) - Fc;
}

/* BCC initialization in 3d */
void set_position(body *particle)
{
    int n = 0; while(2 * n * n * n < n_particles ) n++;
    int i,j,k;
    int l = 0;
    for(i = 0; i < n && l < n_particles/2; i++)
        for(j = 0; j < n && l < n_particles/2; j++)
            for(k = 0; k < n && l < n_particles/2; k++){
                particle[l].pos[0] = i*L/n;
                particle[l].pos[1] = j*L/n;
                particle[l].pos[2] = k*L/n;
                particle[n_particles/2+l].pos[0] = (i+0.5)*L/n;
                particle[n_particles/2+l].pos[1] = (j+0.5)*L/n;
                particle[n_particles/2+l].pos[2] = (k+0.5)*L/n;
                l++;
            }
}

/* periodic boundary conditions */
double PBC(double x)
{
    while(x < -0.5*L){x += L;}
    while(x >= 0.5*L){x -= L;}
    return x;
} 

void get_table(body *particle)
{
    int i,j,k;
    int x[DIMENSION];
    int FOUND_FLAG;
    double r2, dr[DIMENSION];
    int count;
    for(i = 0; i < n_particles-1; i++){
        count = 0;
        for(j = i+1; j < n_particles; j++){
            FOUND_FLAG = 0;
            for(x[0] = -1; x[0] <= 1 ; x[0]++){
                for(x[1] = -1; x[1] < 1 ; x[1]++){
                    for(x[2] = -1; x[2] < 1; x[2]++){
                        if(!FOUND_FLAG){
                            r2 = 0;
                            for(k = 0; k < DIMENSION; k++){
                                dr[k] = x[k]*L + PBC(particle[j].pos[k]) - PBC(particle[i].pos[k]);
                                r2 += dr[k]*dr[k];
                            }
                            if(r2 < Rc*Rc ){
                                FOUND_FLAG = 1;
                                table[i][count+1] = j;
                                count++;
                            }
                        }
                    }
                }
            }
        }
        table[i][0] = count;
    }
}

/* use table of neighbors */
void get_acc_table(body *particle)
{
    int i,j,k;
    double r, r2, dr[DIMENSION];

    /* initialize energy and accelerations to zero */
    U = 0;

    for(i = 0; i < n_particles; i++){
        for(k = 0; k < DIMENSION; k++){
            particle[i].acc[k] = 0;
        }
    }

    /* determine interaction for each pair of particles (i,j) */
    for(i = 0; i < n_particles-1; i++){
        for(j = 0; j < table[i][0]; j++){
            r2 = 0;
            for(k = 0; k < DIMENSION; k++){
                dr[k] = PBC(particle[i].pos[k] - particle[table[i][j]].pos[k]);
                r2 += dr[k]*dr[k];
            }
            if( r2 < Rc*Rc ){
                r = sqrt(r2);
                U += potential(r);
                for(k = 0; k < DIMENSION; k++){
                    particle[i].acc[k] += force(r)*dr[k]/r;
                    particle[table[i][0]].acc[k] -= force(r)*dr[k]/r;
                }
            }
        }
    }
}

/* function to compute forces */
void get_acc(body *particle)
{
    int i,j,k;
    double r, r2, dr[DIMENSION];

    /* initialize energy and accelerations to zero */
    U = 0;

    for(i = 0; i < n_particles; i++){
        for(k = 0; k < DIMENSION; k++){
            particle[i].acc[k] = 0;
        }
    }

    /* determine interaction for each pair of particles (i,j) */
    for(i = 0; i < n_particles-1; i++){
        for(j = i+1; j < n_particles; j++){
            r2 = 0;
            for(k = 0; k < DIMENSION; k++){
                dr[k] = PBC(particle[i].pos[k] - particle[j].pos[k]);
                r2 += dr[k]*dr[k];
            }
            if( r2 < Rc*Rc ){
                r = sqrt(r2);
                U += potential(r);
                for(k = 0; k < DIMENSION; k++){
                    particle[i].acc[k] += force(r)*dr[k]/r;
                    particle[j].acc[k] -= force(r)*dr[k]/r;
                }
            }
        }
    }
}

void set_temperature(body *particle, double temp)
{
    int i,j;
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] *= sqrt(temp/T);
}

void init(body *particle)
{
    Uc = 4 * ( pow(1/Rc,12) - pow(1/Rc,6) );
    Fc = 24 * ( 2 * pow(1/Rc,13) - pow(1/Rc,7) );

    L = cbrt(n_particles/rho);

    set_position(particle);

    /* generate momenta */
    srand(time(NULL));

    K = 0;

    int i,j;
    double drift[DIMENSION] = {0.0f};
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++){
            drift[j] += particle[i].mom[j] = 2*(rand()/(double)RAND_MAX)-1;
            K += 0.5*particle[i].mom[j]*particle[i].mom[j];
        }

    /* boost in the center of mass frame */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] -= drift[j]/n_particles;

    /* set the desired temperature */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] *= sqrt(3*n_particles*T/(2*K));

    T = 2*K/(3*n_particles);

    /* create table of neighbors */
    table = (int**)malloc(n_particles*sizeof(int*));
    for(i = 0; i < n_particles; i++)
        table[i] = (int*)malloc(n_particles*sizeof(int));
    get_table(particle);

    get_acc(particle);

    /* total energy */
    H = U + K;
}

/* velocity verlet */
void integrate(body *particle)
{
    /* compute intermediate momentum v(t+½dt) = v(t) + ½a(t)dt */
    int i,j;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++){
            particle[i].mom[j] += 0.5 * time_step * particle[i].acc[j];
        }
    }

    /* compute new position r(t+dt) = r(t) + v(t)dt + ½a(t)dt² */
    /*                              = r(t) + v(t+½dt)dt        */
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++){
            particle[i].pos[j] += time_step * particle[i].mom[j];
        }
    }

    /* compute new acceleration a(t+dt) = f(r(t+dt))           */
    get_acc(particle);

    /* compute new momentum v(t+dt) = v(t) + ½(a(t)+a(t+dt))dt */
    /*                              = v(t+½dt) + ½a(t+dt)dt    */
    K = 0;
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++){
            particle[i].mom[j] += 0.5 * time_step * particle[i].acc[j];
            K += particle[i].mom[j]*particle[i].mom[j]/2;
        }
    }

    T = 2*K/(3*n_particles);
    H = U + K;
}

#endif
