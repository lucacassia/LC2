#ifndef VEC3
#define VEC3

#include <math.h>
#include <stdlib.h>

#define _rand() (rand()/(float)RAND_MAX)

typedef struct _vec3{
    double x,y,z;
}vec3;

vec3 vec3_new(double X, double Y, double Z)
{
    vec3 tmp = {.x = X, .y = Y, .z = Z};
    return tmp;
}

double vec3_dot(vec3 a, vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vec3_mod(vec3 a)
{
    return sqrt( vec3_dot(a,a) );
}

typedef struct _body{
    vec3 r, v, c;
    struct _body *prev;
    struct _body *next;
}body;

#endif
