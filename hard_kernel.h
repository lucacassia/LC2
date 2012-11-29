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
int N = 5;
double ETA = 0.2;
double SIGMA;
double runtime;
double pressure;
double min_time;

double get_min()
{
    int i,j;
    double minimum = ctimes[1];
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
    double dx, dy, dz, rr, rv, vv, delta, collision_time = DBL_MAX;

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

                if(rv <= 0 && delta >= 0){
                    if((-rv-sqrt(delta))/vv < collision_time)
                        collision_time = (-rv-sqrt(delta))/vv;
                }
            }
        }
    }
    return collision_time;
}

void collide()
{
    int i, j;
    for(i = 0; i < N; i++){
        for(j = i+1; j < N; j++){
            if(i == collider1 || j == collider2 || j == collider1 || i == collider2){
                ctimes[i*N+j] = get_collision_time(i,j);
            }else ctimes[i*N+j] -= min_time;
        }
    }
}

void init()
{
    srand(time(NULL));
    if(particle != NULL) free(particle);
    if(ctimes != NULL) free(ctimes);
    particle = (body*)malloc(N*sizeof(body));
    ctimes = (double*)malloc(N*N*sizeof(body));

    SIGMA = cbrt(1.909859317*ETA/N);
    pressure = 0;
    runtime = 0;

    int i,j,k;
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
    collider2 = 1;

    for(i = 0; i < N; i++){
        for(j = i+1; j < N; j++){
            ctimes[i*N+j] = get_collision_time(i,j);
        }
    }
    runtime += min_time = get_min();
}

void run()
{
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

    vec3 dr, dv;
    dr.x = particle[collider2].r.x - particle[collider1].r.x;
    dr.y = particle[collider2].r.y - particle[collider1].r.y;
    dr.z = particle[collider2].r.z - particle[collider1].r.z;

    dv.x = particle[collider1].v.x - particle[collider2].v.x;
    dv.y = particle[collider1].v.y - particle[collider2].v.y;
    dv.z = particle[collider1].v.z - particle[collider2].v.z;

    particle[collider1].v.x -= vec3_dot(dv,dr)*dr.x;
    particle[collider1].v.y -= vec3_dot(dv,dr)*dr.y;
    particle[collider1].v.z -= vec3_dot(dv,dr)*dr.z;

    particle[collider2].v.x += vec3_dot(dv,dr)*dr.x;
    particle[collider2].v.y += vec3_dot(dv,dr)*dr.y;
    particle[collider2].v.z += vec3_dot(dv,dr)*dr.z;

    collide();

    pressure += SIGMA * vec3_mod(dv)/2;
    runtime += min_time = get_min();
}


