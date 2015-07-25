#ifndef NEWLIB
#define NEWLIB

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

double H,K,U,T;
double L,rc,rm,Uc,dF;
double dt;

double potential(double r)
{
    if(r < rc) return (( 4*(1/(pow(r,12))-1/(pow(r,6)))) - Uc - dF*(r-rc));
    return 0;
}

double force(double r)
{
    return (24*(2*pow(1/r,13) - pow(1/r,7))+ dF);
}

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

void increment(int *counter, int min, int max, int left)
{
    counter[0]++;
    if(counter[0] == max){
        counter[0] = min;
        if(left>1) increment(&counter[1],min,max,left-1);
    }
}

void init_pos(obj list[], int N, double offset)
{
    int index[DIMENSION] = {0};
    int i,j,k = 0;
    while(ipow(k,DIMENSION) < N) k++;

    for(i = 0; i < N; i++){
        for(j = 0; j < DIMENSION; j++)
            list[i].pos[j] = (offset + index[j]) * L / k;
        increment(index,0,k,DIMENSION);
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

void reset_mom(obj list[], int N, double y)
{
    int i,j;
    K = 0.0f;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++){
            list[i].mom[j] *= sqrt(y);
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

double PBC(double x)
{
    while(x >  L) x -= L;
    while(x <= 0) x += L;
    return x;
}

double distPBC(double x)
{
    while(x >= 0.5 * L) x -= L;
    while(x < -0.5 * L) x += L;
    return x;
}

void compute_table(obj list[], int **table, int N)
{
    int i,j,k;
    double r2,r[DIMENSION];
    for(i = 0; i < N; i++){
        table[i][0] = 0;
        for(j = 0; j < N; j++){
            r2 = 0.0f;
            for(k = 0; k < DIMENSION; k++){
                r[k] = distPBC(list[j].pos[k] - list[i].pos[k]);
                r2 += r[k] * r[k];
            }
            if((i!=j)&&(r2 < rm*rm)){
                table[i][0]++;
                table[i][table[i][0]] = j;
            }
        }
    }
}

void get_acc(obj list[], int **table, int N)
{
    int i,j,k;
    double r[DIMENSION],tmp;
    for(i = 0; i < N; i++)
        for(k = 0; k < DIMENSION; k++)
            list[i].acc[k] = 0.0f;

    U = 0.0f;

    for(i = 0; i < N; i++){
        for(j = 0; j < table[i][0]; j++){
            tmp = 0.0f;
            for(k = 0; k < DIMENSION; k++){
                r[k] = distPBC(list[table[i][j+1]].pos[k] - list[i].pos[k]);
                tmp += r[k] * r[k];
            }
            if(tmp < rc*rc){
                tmp = sqrt(tmp);
                U += potential(tmp);
                tmp = force(tmp)/tmp;
                for(k = 0; k < DIMENSION; k++){
                    list[i].acc[k] -= tmp*r[k];
                    list[table[i][j+1]].acc[k] += tmp*r[k];
                }
            }
        }
    }
}

void integrate(obj list[],int **table, int N)
{
    int i,j;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++){
            list[i].mom[j] += 0.5 * list[i].acc[j] * dt;
            list[i].pos[j] = PBC(list[i].pos[j] + list[i].mom[j] * dt);
        }
    get_acc(list,table,N);
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
