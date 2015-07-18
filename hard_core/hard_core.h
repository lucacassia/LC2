#include <float.h>
#include <string.h>
#include <stdio.h>

#include "mersenne.h"
#include "vec3.h"

typedef struct body{
    double pos[DIMENSION];
    double mom[DIMENSION];
}body;

body *particle = NULL;
double **collision_table = NULL;
body *data = NULL;
double *dtimes = NULL;
int *ptr = NULL;

int collider1, collider2;
int n_particles = 250;
int n_history = 10000;
double ETA = 0.2;
double SIGMA;

double runtime;
double min_time;
double pressure;
double dp;
double kinetic;
double temperature = 1.0;
double mfp;
double dmfp;
int hits;

double get_kinetic()
{
    double tmp = 0;
    int k;
    for(k = 0; k < n_particles; k++)
        tmp += scalar(particle[k].mom,particle[k].mom);
    return tmp/2;
}

double get_min()
{
    int i,j;
    collider1 = 0;
    collider2 = 1;
    double minimum = collision_table[collider1][collider2];
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(collision_table[i][j] <= minimum){
                minimum = collision_table[i][j];
                collider1 = i;
                collider2 = j;
            }
    return minimum;
}

double get_collision_time(int i, int j)
{
    double dr[DIMENSION], dv[DIMENSION];
    double t, dx, dy, dz, rr, rv, vv, delta, collision_time = DBL_MAX;

    for(dx = -1; dx <= 1 ; dx++){
        for(dy = -1; dy <= 1; dy++){
            for(dz = -1; dz <= 1; dz++){
                dr[0] = dx + particle[j].pos[0] - particle[i].pos[0];
                dr[1] = dy + particle[j].pos[1] - particle[i].pos[1];
                dr[2] = dz + particle[j].pos[2] - particle[i].pos[2];

                dv[0] = particle[j].mom[0] - particle[i].mom[0];
                dv[1] = particle[j].mom[1] - particle[i].mom[1];
                dv[2] = particle[j].mom[2] - particle[i].mom[2];

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
    }
    return collision_time;
}

void collide()
{
    int i, j;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(i == collider1 || j == collider1 || i == collider2 || j == collider2 || collider1 == collider2)
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
    if(data != NULL)
        free(data);
    if(dtimes != NULL)
        free(dtimes);
    if(ptr != NULL)
        free(ptr);
}

void reset()
{
    runtime = 0;
    dp = 0;
    hits = 0;
}

void init()
{
    int i,j,k,l,n;
    srand(time(NULL));
    seed_mersenne( (long)time(NULL) );
    for(n = 0; n < 543210; n++) mersenne();

    n = 0;
    while(2*n*n*n < n_particles) n++;
    SIGMA = cbrt(ETA*1.909859317/n_particles);

    clear();
    particle = (body*)malloc(n_particles*sizeof(body));
    collision_table = (double**)malloc(n_particles*sizeof(double*));
    for(i = 0; i < n_particles; i++)
        collision_table[i] = (double*)malloc(n_particles*sizeof(double));
    data = (body*)malloc(n_particles*n_history*sizeof(body));
    dtimes = (double*)malloc(n_particles*n_history*sizeof(double));
    ptr = (int*)malloc(n_particles*sizeof(int));

    for(l = i = 0; i < n && l < n_particles/2; i++)
        for(j = 0; j < n && l < n_particles/2; j++)
            for(k = 0; k < n && l < n_particles/2; k++){
                particle[l].pos[0] = i*1.0/n;
                particle[l].pos[1] = j*1.0/n;
                particle[l].pos[2] = k*1.0/n;
                particle[n_particles/2+l].pos[0] = 1.0/n/2.0 + i*1.0/n;
                particle[n_particles/2+l].pos[1] = 1.0/n/2.0 + j*1.0/n;
                particle[n_particles/2+l].pos[2] = 1.0/n/2.0 + k*1.0/n;
                l++;
            }

    double tmp[DIMENSION] = {0};
    for(k = 0; k < n_particles; k++){
        tmp[0] += particle[k].mom[0] = 2*mersenne()-1;
        tmp[1] += particle[k].mom[1] = 2*mersenne()-1;
        tmp[2] += particle[k].mom[2] = 2*mersenne()-1;
    }

    for(k = 0; k < n_particles; k++){
        particle[k].mom[0] -= tmp[0]/n_particles;
        particle[k].mom[1] -= tmp[1]/n_particles;
        particle[k].mom[2] -= tmp[2]/n_particles;
    }
    double norm = 0;
    for(k = 0; k < n_particles; k++)
        norm += scalar(particle[k].mom, particle[k].mom);
    norm = sqrt( norm / (3 * n_particles * temperature) );
    for(k = 0; k < n_particles; k++){
        particle[k].mom[0] /= norm;
        particle[k].mom[1] /= norm;
        particle[k].mom[2] /= norm;
        ptr[k] = 0;
    }

    collider1 = 0;
    collider2 = 0;

    kinetic = get_kinetic();
    temperature = 2*kinetic/(3*n_particles);

    collide();
    reset();
}

void run()
{
    min_time = get_min();

    double dr[DIMENSION], dv[DIMENSION], tmp[DIMENSION];

    int k;
    for(k = 0; k < n_particles; k++){
        particle[k].pos[0] += particle[k].mom[0] * min_time;
        particle[k].pos[1] += particle[k].mom[1] * min_time;
        particle[k].pos[2] += particle[k].mom[2] * min_time;

        particle[k].pos[0] -= floor(particle[k].pos[0]);
        particle[k].pos[1] -= floor(particle[k].pos[1]);
        particle[k].pos[2] -= floor(particle[k].pos[2]);
    }

    dr[0] = particle[collider2].pos[0] - particle[collider1].pos[0];
    dr[1] = particle[collider2].pos[1] - particle[collider1].pos[1];
    dr[2] = particle[collider2].pos[2] - particle[collider1].pos[2];

    double dx, dy, dz;
    for(dx = -1; dx <= 1 ; dx++){
        for(dy = -1; dy <= 1; dy++){
            for(dz = -1; dz <= 1; dz++){
                tmp[0] = dx + particle[collider2].pos[0] - particle[collider1].pos[0];
                tmp[1] = dy + particle[collider2].pos[1] - particle[collider1].pos[1];
                tmp[2] = dz + particle[collider2].pos[2] - particle[collider1].pos[2];

                if(scalar(tmp,tmp) < scalar(dr,dr)){
                    for(k = 0; k < DIMENSION; k++)
                        dr[k] = tmp[k];
                }
            }
        }
    }

    dv[0] = particle[collider1].mom[0] - particle[collider2].mom[0];
    dv[1] = particle[collider1].mom[1] - particle[collider2].mom[1];
    dv[2] = particle[collider1].mom[2] - particle[collider2].mom[2];

    tmp[0] = scalar(dv,dr)*dr[0]/scalar(dr,dr);
    tmp[1] = scalar(dv,dr)*dr[1]/scalar(dr,dr);
    tmp[2] = scalar(dv,dr)*dr[2]/scalar(dr,dr);

    particle[collider1].mom[0] -= tmp[0];
    particle[collider1].mom[1] -= tmp[1];
    particle[collider1].mom[2] -= tmp[2];

    particle[collider2].mom[0] += tmp[0];
    particle[collider2].mom[1] += tmp[1];
    particle[collider2].mom[2] += tmp[2];

    collide();

    data[ptr[collider1]*n_particles+collider1] = particle[collider1];
    data[ptr[collider2]*n_particles+collider2] = particle[collider2];
    dtimes[ptr[collider1]*n_particles+collider1] = runtime;
    dtimes[ptr[collider2]*n_particles+collider2] = runtime;
    ptr[collider1] = (ptr[collider1]+1)%n_history;
    ptr[collider2] = (ptr[collider2]+1)%n_history;

    hits++;
    runtime += min_time;
    dp += module(dv);
    pressure = n_particles*temperature*(1+SIGMA*dp/(2*kinetic*runtime));
}

void get_mfp()
{
    int i,j;
    double tmp[n_particles];
    double dr[DIMENSION];
    for(j = 0; j < n_particles; j++){
        for(tmp[j] = i = 0; i < n_history-1; i++){
            dr[0] = data[(ptr[j]+i+1)*n_particles+j].pos[0] - data[(ptr[j]+i)*n_particles+j].pos[0];
            dr[1] = data[(ptr[j]+i+1)*n_particles+j].pos[1] - data[(ptr[j]+i)*n_particles+j].pos[1];
            dr[2] = data[(ptr[j]+i+1)*n_particles+j].pos[2] - data[(ptr[j]+i)*n_particles+j].pos[2];
            tmp[j] += module(dr);
        }
        tmp[j] /= n_history;
    }
    mfp = dmfp = 0;
    for(j = 0; j < n_particles; j++){
        mfp += tmp[j];
    }
    mfp /= n_particles;
    for(j = 0; j < n_particles; j++){
        dmfp += (tmp[j]-mfp)*(tmp[j]-mfp);
    }
    dmfp = sqrt(dmfp/(n_particles*n_particles));
}

void print()
{
    FILE *v = fopen("speed.dat","a");
    FILE *f = fopen("data.dat","a");
    FILE *t = fopen("times.dat","w");

    int i,k;
    for(k = 0; k < n_particles; k++){
        for(i = 0; i < n_history-1; i++){
            fprintf(t, "%e\n", dtimes[(ptr[k]+i+1)*n_particles+k] - dtimes[(ptr[k]+i)*n_particles+k]);
        }
    }

    for(k = 0; k < n_particles; k++){
        fprintf(v, "%e\t%e\t%e\n", particle[k].mom[0], particle[k].mom[1], particle[k].mom[2]);
    }

    fprintf(f, "%d\t%lf\t%lf\t%lf\t%e\n", n_particles, ETA, pressure, temperature, SIGMA*dp/(2*kinetic*runtime) );

    fclose(t);
    fclose(v);
    fclose(f);
}

