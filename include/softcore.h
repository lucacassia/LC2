#ifndef SOFTCORE
#define SOFTCORE

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int N;
double H,K,U,T;
double rho,L;
double rc = 2.5f;
double rm = 2.8f;
double Fc = -0.039;
double Uc = -0.0163;
double dt = 0.001;

double potential(double r)
{
    if(r < rc) return 4*(pow(r,-12)-pow(r,-6)) - Uc + (r-rc)*Fc;
    else return 0;
}

double force(double r)
{
    if(r < rc) return 24*(2*pow(r,-13) - pow(r,-7)) - Fc;
    else return 0;
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

void init_pos(obj list[], int n, double offset)
{
    int index[DIMENSION] = {0};
    int i,j,k = 0;
    while(ipow(k,DIMENSION) < n) k++;

    for(i = 0; i < n; i++){
        for(j = 0; j < DIMENSION; j++)
            list[i].pos[j] = (offset + index[j]) * L / k;
        increment(index,0,k,DIMENSION);
    }
}

void init_mom(obj list[])
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

void reset_mom(obj list[], double y)
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

void destroy_table(int **table)
{
    if(table){
        int i;
        for(i = 0; i < N; i++)
            if(table[i])
                free(table[i]);
        free(table);
    }
}

int **create_table(int **table)
{
    destroy_table(table);
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

void compute_full_table(obj list[], int **table)
{
    int i,j,k;
    int FOUND_FLAG;
    int l,lmax = ipow(3,DIMENSION);
    int index[DIMENSION];
    double r2,r[DIMENSION];

    for(i = 0; i < N; i++){
        table[i][0] = 0;
        for(j = 0; j < N; j++)if(i!=j){
            FOUND_FLAG = 0;
            for(k = 0; k < DIMENSION; k++) index[k] = -1;
            for(l = 0; l < lmax && !FOUND_FLAG; l++){
                for(k = 0; k < DIMENSION; k++) r[k] = index[k] * L + list[j].pos[k] - list[i].pos[k];
                r2 = scalar(r,r);
                FOUND_FLAG = (r2 < rm*rm);
                increment(index,-1,2,DIMENSION);
            }
            if(FOUND_FLAG){
                table[i][0]++;
                table[i][table[i][0]] = j;
            }
        }
    }
}

void compute_table(obj list[], int **table)
{
    int i,j,k;
    int FOUND_FLAG;
    int l,lmax = ipow(3,DIMENSION);
    int index[DIMENSION];
    double r2,r[DIMENSION];

    for(i = 0; i < N; i++){
        table[i][0] = 0;
        for(j = i+1; j < N; j++){
            FOUND_FLAG = 0;
            for(k = 0; k < DIMENSION; k++) index[k] = -1;
            for(l = 0; l < lmax && !FOUND_FLAG; l++){
                for(k = 0; k < DIMENSION; k++) r[k] = index[k] * L + list[j].pos[k] - list[i].pos[k];
                r2 = scalar(r,r);
                FOUND_FLAG = (r2 < rm*rm);
                increment(index,-1,2,DIMENSION);
            }
            if(FOUND_FLAG){
                table[i][0]++;
                table[i][table[i][0]] = j;
            }
        }
    }
}

void get_acc(obj list[], int **table)
{
    U = 0.0f;

    int i,j,k;
    for(i = 0; i < N; i++)
        for(k = 0; k < DIMENSION; k++)
            list[i].acc[k] = 0.0f;

    double r2,modr;
    double r[DIMENSION];
    int l,lmax = ipow(3,DIMENSION);
    int index[DIMENSION];
    int FOUND_FLAG;
    for(i = 0; i < N; i++){
        for(j = 0; j < table[i][0]; j++){
            FOUND_FLAG = 0;
            for(k = 0; k < DIMENSION; k++) index[k] = -1;
            for(l = 0; l < lmax && !FOUND_FLAG; l++){
                for(k = 0; k < DIMENSION; k++) r[k] = index[k] * L + list[table[i][1+j]].pos[k] - list[i].pos[k];
                r2 = scalar(r,r);
                FOUND_FLAG = (r2 < rc*rc);
                increment(index,-1,2,DIMENSION);
            }
            if(FOUND_FLAG){
                modr = sqrt(r2);
                U += potential(modr);
                for(k = 0; k < DIMENSION; k++){
                    r[k] *= force(modr)/modr;
                    list[i].acc[k] -= r[k];
                    list[table[i][1+j]].acc[k] += r[k];
                }
            }
        }
    }
}

void integrate(obj list[],int **table)
{
    int i,j;
    for(i = 0; i < N; i++)
        for(j = 0; j < DIMENSION; j++){
            list[i].mom[j] += 0.5 * list[i].acc[j] * dt;
            list[i].pos[j] = PBC(list[i].pos[j] + list[i].mom[j] * dt);
        }
    get_acc(list,table);
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
