#include <float.h>
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

body *particle = NULL;
double *ctimes = NULL;
int collider1, collider2;
int N = 256;
double ETA;
double SIGMA;
double runtime;
double pressure;

double get_min()
{
    int i,j;
    double minimum = DBL_MAX;
    for(i = 0; i < N; i++)
        for(j = i+1; j < N; j++)
            if(ctimes[i*N+j] < minimum){
                minimum = ctimes[i*N+j];
                collider1 = i;
                collider2 = j;
            }
    return minimum;
}

void collide()
{
    int i, j;
    vec3 dr, dv;
    double dx, dy, dz, rr, rv, vv, delta, collision_time;
    for(i = 0; i < N; i++){
        for(j = i+1; j < N; j++){
            if(i == collider1 || i == collider2 || j == collider1 || j == collider2 || collider1 == collider2){
                collision_time = DBL_MAX;
                for(dx = -1; dx <= 1 ; dx++){
                    for(dy = -1; dy <= 1; dy++){
                        for(dz = -1; dz <= 1; dz++){
                            _vec3_sub(dr,particle[j].r,particle[i].r);
                            _vec3_sub(dv,particle[j].v,particle[i].v);
                            dr.x += dx;
                            dr.y += dy;
                            dr.z += dz;
                            rr = _vec3_dot(dr, dr);
                            rv = _vec3_dot(dr, dv);
                            vv = _vec3_dot(dv, dv);
                            delta = rv*rv-vv*(rr-SIGMA*SIGMA);

                            if(rv <= 0 && delta >= 0){
                                if(min((-rv+sqrt(delta))/vv, (-rv-sqrt(delta))/vv) < collision_time)
                                    collision_time = min((-rv+sqrt(delta))/vv, (-rv-sqrt(delta))/vv);
                            }
                        }
                    }
                }
                ctimes[i*N+j] = collision_time;
            }
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

    collider1 = 0;
    collider2 = 0;

    int k;
    vec3 tmp = {.x = 0, .y = 0, .z = 0};
    for(k = 1; k < N; k++){
        particle[k].r = VEC3(_rand(), _rand(), _rand());
        particle[k].v = VEC3(_rand()*2-1, _rand()*2-1, _rand()*2-1);
        _vec3_add(tmp, tmp, particle[k].v);
    }
    particle[0].r = VEC3(_rand(), _rand(), _rand());
    particle[0].v = VEC3(-tmp.x, -tmp.y, -tmp.z);

    collide();
}

void run()
{
    double min_time = get_min();

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
    _vec3_sub(dr, particle[collider2].r, particle[collider1].r);
    _vec3_sub(dv, particle[collider1].v, particle[collider2].v);

    particle[collider1].r.x -= _vec3_dot(dv,dr)*dr.x;
    particle[collider1].r.y -= _vec3_dot(dv,dr)*dr.y;
    particle[collider1].r.z -= _vec3_dot(dv,dr)*dr.z;

    particle[collider2].r.x += _vec3_dot(dv,dr)*dr.x;
    particle[collider2].r.y += _vec3_dot(dv,dr)*dr.y;
    particle[collider2].r.z += _vec3_dot(dv,dr)*dr.z;

    collide();

    pressure += SIGMA*_vec3_mod(dv)/2;
    runtime += min_time;
}

int main()
{
    int k;
    FILE *f = fopen("pressure.dat","w");
    for(ETA = 0.01; ETA < 0.5; ETA += 0.01){
        init();
        for(k = 0; k < 1e4; k++){
            run();
        }
        fprintf(f, "%lf\t%e\n", ETA, 1+pressure/runtime);
    }
    fclose(f);
    free(particle);
    free(ctimes);
    return 0;
}
