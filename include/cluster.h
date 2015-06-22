#ifndef CLUSTER
#define CLUSTER

#include <stdlib.h>

typedef struct _spin{
    int s;
    struct _spin *cl;
    unsigned int l, u;
}spin;

spin *cl_find(spin *x) {
    while(x->cl != x)
        x = x->cl;
    return x;
}

spin *cl_merge(spin *x, spin *y) {
    return cl_find(x)->cl = cl_find(y);
}

#endif
