#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define _vec3_add(a,b,c) \
    (a).x=(b).x+(c).x; \
    (a).y=(b).y+(c).y; \
    (a).z=(b).z+(c).z

#define _vec3_sub(a,b,c) \
    (a).x=(b).x-(c).x; \
    (a).y=(b).y-(c).y; \
    (a).z=(b).z-(c).z

#define _vec3_dot(a,b) \
    ((a).x*(b).x+(a).y*(b).y+(a).z*(b).z)

#define _vec3_mod(a) \
    sqrt(pow((a).x,2)+pow((a).y,2)+pow((a).z,2))

#define _rand() \
    (rand()/(float)RAND_MAX)

double min(double a, double b)
{
    if(a > b) return b;
    else return a;
}

typedef struct vec3{
    double x,y,z;
}vec3;

vec3 VEC3(double X, double Y, double Z){
    vec3 tmp = {.x = X, .y = Y, .z = Z};
    return tmp;
}

typedef struct _body{
    vec3 r, v;
}body;

body *particles = NULL;
double *ctimes = NULL;
int collider1, collider2;
int N = 500;
double ETA;
double SIGMA;
double runtime;
double pressure;
double min_collision_time;

void collide()
{
    int i, j;
    vec3 dr,dv;
    for(i = 0; i < N; i++){
        for(j = i+1; j < N; j++){
            if(i == collider1 || i == collider2 || j == collider1 || j == collider2){
                _vec3_sub(dr,particles[j].r,particles[i].r);
                _vec3_sub(dv,particles[j].v,particles[i].v);
                double rr = _vec3_dot(dr, dr);
                double rv = _vec3_dot(dr, dv);
                double vv = _vec3_dot(dv, dv);
                double delta = rv*rv-vv*(rr-SIGMA*SIGMA);

                if(rv <= 0 && delta >= 0){
                    double collision_time = min((-rv+sqrt(delta))/vv, (-rv-sqrt(delta))/vv);
                    ctimes[2*i*N-i-i*i+j-1] = collision_time;
                    if(collision_time < min_collision_time){
                        min_collision_time = collision_time;
                        collider1 = i;
                        collider2 = j;
                    }
                }
            }
        }
    }
}

void init()
{
    srand(time(NULL));
    if(particles != NULL) free(particles);
    if(ctimes != NULL) free(ctimes);
    particles = (body*)malloc(N*sizeof(body));
    ctimes = (double*)malloc(((N*(N-1))/2)*sizeof(body));

    SIGMA = cbrt(1.909859317*ETA/N);
    pressure = 0;
    runtime = 0;

    collider1 = 0;
    collider2 = 0;

    int k;
    vec3 tmp = {.x = 0, .y = 0, .z = 0};
    for(k = 1; k < N; k++){
        particles[k].r = VEC3(_rand(), _rand(), _rand());
        particles[k].v = VEC3(_rand()*2-1, _rand()*2-1, _rand()*2-1);
        _vec3_add(tmp, tmp, particles[k].v);
    }
    particles[0].r = VEC3(_rand(), _rand(), _rand());
    particles[0].v = VEC3(-tmp.x, -tmp.y, -tmp.z);
    for(k = 0; k < (N*(N-1))/2; k++)
        ctimes[k] = 1e10;

    collide();
}

void update()
{
    int i = collider1, j = collider2, k;
    vec3 dr, dv;
    for(k = 0; k < N; k++){
        particles[k].r.x += particles[k].v.x * min_collision_time;
        particles[k].r.y += particles[k].v.y * min_collision_time;
        particles[k].r.z += particles[k].v.z * min_collision_time;

        while(particles[k].r.x > 1) particles[k].r.x -= 1;
        while(particles[k].r.y > 1) particles[k].r.y -= 1;
        while(particles[k].r.z > 1) particles[k].r.z -= 1;
        while(particles[k].r.x < 0) particles[k].r.x += 1;
        while(particles[k].r.y < 0) particles[k].r.y += 1;
        while(particles[k].r.z < 0) particles[k].r.z += 1;
    }

    _vec3_sub(dr, particles[j].r, particles[i].r);
    _vec3_sub(dv, particles[j].v, particles[i].v);

    particles[i].r.x += -_vec3_dot(dv,dr)*dr.x;
    particles[i].r.y += -_vec3_dot(dv,dr)*dr.y;
    particles[i].r.z += -_vec3_dot(dv,dr)*dr.z;

    particles[j].r.x = _vec3_dot(dv,dr)*dr.x;
    particles[j].r.y = _vec3_dot(dv,dr)*dr.y;
    particles[j].r.z = _vec3_dot(dv,dr)*dr.z;

    pressure += SIGMA*_vec3_mod(dv)/2;
    runtime += min_collision_time;
}

int main()
{
    int k;
    FILE *f = fopen("pressure.dat","w");
    for(ETA = 0.01; ETA < 0.02; ETA += 0.01){
        init();
        for(k = 0; k < 1e4; k++){
            collide();
            update(min_collision_time, collider1, collider2);
        }
        fprintf(f, "%lf\t%e\n", ETA, 1+pressure/runtime);
    }
    fclose(f);
    free(particles);
    free(ctimes);
    return 0;
}
