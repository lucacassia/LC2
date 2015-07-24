#ifndef NEWLIB
#define NEWLIB

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

double H,K,U,T;

typedef struct obj{
    double pos[DIMENSION];
    double mom[DIMENSION];
    double acc[DIMENSION];
}obj;

double modulus(double v[])
{
    double tmp = 0.0f;
    int i;
    for(i = 0; i < DIMENSION; i++)
        tmp += v[i]*v[i];
    return sqrt(tmp);
}

double scalar(double a[], double b[])
{
    double tmp = 0.0f;
    int i;
    for(i = 0; i < DIMENSION; i++)
        tmp += a[i]*b[i];
    return tmp;
}

int ipow(int base, int exp)
{
    int result = 1;
    while(exp){
        if(exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

void increment(int *counter, int max, int left)
{
    counter[0]++;
    if(counter[0] == max){
        counter[0] = 0;
        if(left>1) increment(&counter[1],max,left-1);
    }
}

void init_pos(obj list[], int N, double L, double offset)
{
    int index[DIMENSION] = {0};
    int i,j,k = 0;
    while(ipow(k,DIMENSION) < N) k++;

    for(i = 0; i < N; i++){
        for(j = 0; j < DIMENSION; j++)
            list[i].pos[j] = (offset + index[j]) * L / k;
        increment(index,k,DIMENSION);
    }    
}

void init_mom(obj list[], int N)
{
    int i,j;
    srand(time(NULL));

    double drift[DIMENSION] = {0.0f};
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++)
            drift[j] += list[i].mom[j] = 2 * (rand() / (double)RAND_MAX ) - 1;

    K = 0.0f;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++){
            list[i].mom[j] -= drift[j] / N;
            K += list[i].mom[j] * list[i].mom[j];
        }
    T = K/(DIMENSION*N);
    K = K/2;
}

void reset_mom(obj list[], int N, double r)
{
    int i,j;
    K = 0.0f;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++){
            list[i].mom[j] *= sqrt(r);
            K += list[i].mom[j] * list[i].mom[j];
        }
    T = K/(DIMENSION*N);
    K = K/2;
}

void destroy_table(int **table, int N)
{
    if(table){
        int i;
        for(i = 0; i < N; i++)
            if(table[i])
                free(table[i]);
        free(table);
    }
}

int **create_table(int **table, int N)
{
    destroy_table(table,N);
    table = (int**)malloc(N*sizeof(int*));
    int i;
    for(i = 0; i < N; i++){
        table[i] = (int*)malloc(N*sizeof(int));
        table[i][0] = 0;
    }
    return table;
}

void compute_table(obj list[], int **table, int N)
{
    
}

void get_acc(obj list[], int N)
{
    int i,j;
    U = 0.0f;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++)
            list[i].acc[j] = 0.0f;
}

double PBC(double x, double L)
{
    while(x > L) x -= L;
    while(x < 0) x += L;
    return x;
}

void integrate(obj list[], int N, double L, double dt)
{
    int i,j;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++){
            list[i].mom[j] += 0.5 * list[i].acc[j] * dt;
            list[i].pos[j] = PBC(list[i].pos[j] + list[i].mom[j] * dt, L);
        }
    get_acc(list,N);
    K = 0.0f;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++){
            list[i].mom[j] += 0.5 * list[i].acc[j] * dt;
            K += list[i].mom[j] * list[i].mom[j];
        }
    T = K/(DIMENSION*N);
    K = K/2;
    H = K + U;
}


#endif
