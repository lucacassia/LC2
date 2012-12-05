#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define _rand() (rand()/(float)RAND_MAX)

typedef struct vec3{double x,y,z;}vec3;
vec3 VEC3(double X, double Y, double Z){vec3 tmp = {.x = X, .y = Y, .z = Z};return tmp;}
double vec3_mod(vec3 a){return sqrt( a.x * a.x + a.y * a.y + a.z * a.z);}
double vec3_dot(vec3 a, vec3 b){return a.x * b.x + a.y * b.y + a.z * b.z;}
typedef struct _body{vec3 r, v, c;}body;

body *particle = NULL;
double *ctimes = NULL;
int collider1, collider2;
int N = 256;
double ETA = 0.03;
double SIGMA;
double runtime;
double pressure;
double min_time;
double temperature;

double get_kinetic()
{
    double tmp = 0;
    int k;
    for(k = 0; k < N; k++){
        tmp += vec3_dot(particle[k].v,particle[k].v);
    }
    return tmp/2;
}

double get_min()
{
    int i,j;
    double minimum = ctimes[1];
    collider1 = 0;
    collider2 = 1;
    for(i = 0; i < N; i++)
        for(j = i+1; j < N; j++)
            if(ctimes[i*N+j] <= minimum){
                minimum = ctimes[i*N+j];
                collider1 = i;
                collider2 = j;
            }
    return minimum;
}

double get_collision_time(int i, int j)
{
    vec3 dr, dv;
    double t, dx, dy, dz, rr, rv, vv, delta, collision_time = DBL_MAX;

    for(dx = -1; dx <= 1 ; dx++){
        for(dy = -1; dy <= 1; dy++){
            for(dz = -1; dz <= 1; dz++){
                dr.x = dx + particle[j].r.x - particle[i].r.x;
                dr.y = dy + particle[j].r.y - particle[i].r.y;
                dr.z = dz + particle[j].r.z - particle[i].r.z;

                dv.x = particle[j].v.x - particle[i].v.x;
                dv.y = particle[j].v.y - particle[i].v.y;
                dv.z = particle[j].v.z - particle[i].v.z;

                rr = vec3_dot(dr, dr);
                rv = vec3_dot(dr, dv);
                vv = vec3_dot(dv, dv);
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
    for(i = 0; i < N; i++)
        for(j = i+1; j < N; j++)
            ctimes[i*N+j] = get_collision_time(i,j);
}

void clear()
{
    if(particle != NULL)
        free(particle);
    if(ctimes != NULL)
        free(ctimes);
}

void init()
{
    srand(time(NULL));
    clear();
    particle = (body*)malloc(N*sizeof(body));
    ctimes = (double*)malloc(N*N*sizeof(body));

    SIGMA = cbrt(1.909859317*ETA/N);

    int k;
    vec3 tmp = {.x = SIGMA/2, .y = SIGMA/2, .z = SIGMA/2};
    for(k = 0; k < N; k++){
        particle[k].r = tmp;
        tmp.x += SIGMA;
        if(tmp.x > 1-SIGMA/2){
            tmp.x = SIGMA/2;
            tmp.y += SIGMA;
            if(tmp.y > 1-SIGMA/2){
                tmp.y = SIGMA/2;
                tmp.z += SIGMA;
                if(tmp.z > 1-SIGMA/2){
                    printf("\nWay too packed!\n");
                    break;
                }
            }
        }
    }

    tmp = VEC3(0,0,0);
    for(k = 0; k < N; k++){
        particle[k].c = VEC3(_rand(), _rand(), _rand());
        particle[k].v = VEC3(_rand()*2-1, _rand()*2-1, _rand()*2-1);
        tmp.x += particle[k].v.x;
        tmp.y += particle[k].v.y;
        tmp.z += particle[k].v.z;
    }

    for(k = 0; k < N; k++){
        particle[k].v.x -= tmp.x/N;
        particle[k].v.y -= tmp.y/N;
        particle[k].v.z -= tmp.z/N;
    }

    collider1 = 0;
    collider2 = 0;

    collide();
    runtime = min_time = get_min();
    pressure = 0;
}

void run()
{
    printf("\nmin = %e\n(i,j) = (%d,%d)\n",min_time,collider1,collider2);
    int k;
    for(k = 0; k < N; k++){
        particle[k].r.x += particle[k].v.x * min_time;
        particle[k].r.y += particle[k].v.y * min_time;
        particle[k].r.z += particle[k].v.z * min_time;

        particle[k].r.x = fmod(particle[k].r.x,1);
        particle[k].r.y = fmod(particle[k].r.y,1);
        particle[k].r.z = fmod(particle[k].r.z,1);

        if(particle[k].r.x < 0) particle[k].r.x += 1;
        if(particle[k].r.y < 0) particle[k].r.y += 1;
        if(particle[k].r.z < 0) particle[k].r.z += 1;
    }

    vec3 dr, dv, tmp;

    dr.x = particle[collider2].r.x - particle[collider1].r.x;
    dr.y = particle[collider2].r.y - particle[collider1].r.y;
    dr.z = particle[collider2].r.z - particle[collider1].r.z;

    double dx, dy, dz;
    for(dx = -1; dx <= 1 ; dx++){
        for(dy = -1; dy <= 1; dy++){
            for(dz = -1; dz <= 1; dz++){
                tmp.x = dx + particle[collider2].r.x - particle[collider1].r.x;
                tmp.y = dy + particle[collider2].r.y - particle[collider1].r.y;
                tmp.z = dz + particle[collider2].r.z - particle[collider1].r.z;

                if(vec3_mod(tmp) < vec3_mod(dr)){
                    dr = tmp;
                }
            }
        }
    }

    dv.x = particle[collider1].v.x - particle[collider2].v.x;
    dv.y = particle[collider1].v.y - particle[collider2].v.y;
    dv.z = particle[collider1].v.z - particle[collider2].v.z;

    tmp.x = vec3_dot(dv,dr)*dr.x/vec3_dot(dr,dr);
    tmp.y = vec3_dot(dv,dr)*dr.y/vec3_dot(dr,dr);
    tmp.z = vec3_dot(dv,dr)*dr.z/vec3_dot(dr,dr);

    particle[collider1].v.x -= tmp.x;
    particle[collider1].v.y -= tmp.y;
    particle[collider1].v.z -= tmp.z;

    particle[collider2].v.x += tmp.x;
    particle[collider2].v.y += tmp.y;
    particle[collider2].v.z += tmp.z;

    printf("%e\n", vec3_mod(dr));

    collide();

    pressure += vec3_mod(dv);
    runtime += min_time = get_min();
    temperature = get_kinetic();
    printf("\npressure = %e\ntemperature = %e\n", 1+SIGMA*pressure/(2*temperature*runtime), 2*temperature/(3*N));
}

void print()
{
    int k;
    FILE *v = fopen("speed.dat","w");
    FILE *r = fopen("position.dat","w");

    for(k = 0; k < N; k++){
        fprintf(v, "%e\t%e\t%e\n", particle[k].v.x, particle[k].v.y, particle[k].v.z);
        fprintf(r, "%e\t%e\t%e\n", particle[k].r.x, particle[k].r.y, particle[k].r.z);
    }
    fclose(v);
    fclose(r);
}

