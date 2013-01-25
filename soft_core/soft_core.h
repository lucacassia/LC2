#include <string.h>
#include "vec3.h"

int N = 54;
double L = 1.0f;
double dt = 1e-6;
body *particle = NULL;

double temperature = 1.0;
double runtime;

int NDATA = 1000;
double *data = NULL;
double dmax = 0;
int ptr = 0;

void clear(){
    if(particle != NULL)
        free(particle);
    if(data != NULL)
        free(data);
}

void reset(){
    runtime = 0;
}

double get_hamilton(){
    double tmp = 0;
    int i,j;
    double dx,dy,dz;
    for(i = 0; i < N; i++){
        tmp += vec3_dot(particle[i].v, particle[i].v) / 2;
        for(j = i+1; j < N; j++)
            for(dx = -L; dx <= L; dx += L)
                for(dy = -L; dy <= L; dy += L)
                    for(dz = -L; dz <= L; dz += L){
                        vec3 dr;
                        dr.x = dx + particle[j].r.x - particle[i].r.x;
                        dr.y = dy + particle[j].r.y - particle[i].r.y;
                        dr.z = dz + particle[j].r.z - particle[i].r.z;
                        tmp += 4 * (pow(1 / vec3_mod(dr), 12) - pow(1 / vec3_mod(dr), 6));
                    }
    }
    return tmp;
}

double get_temperature(){
    double tmp = 0;
    int i;
    for(i = 0; i < N; i++)
        tmp += vec3_dot(particle[i].v, particle[i].v);
    return tmp / (3 * N);
}

double get_u(){
    double tmp = 0;
    int i,j;
    double dx,dy,dz;
    for(i = 0; i < N; i++)
        for(j = i+1; j < N; j++)
            for(dx = -L; dx <= L; dx += L)
                for(dy = -L; dy <= L; dy += L)
                    for(dz = -L; dz <= L; dz += L){
                        vec3 dr;
                        dr.x = dx + particle[j].r.x - particle[i].r.x;
                        dr.y = dy + particle[j].r.y - particle[i].r.y;
                        dr.z = dz + particle[j].r.z - particle[i].r.z;
                        tmp += 4 * (pow(1 / vec3_mod(dr), 12) - pow(1 / vec3_mod(dr), 6));
                    }
    return tmp / N;
}

void init(){
    int n = 0;
    while(2*n*n*n < N) n++;

    clear();
    particle = (body*)malloc(N*sizeof(body));
    data = (double*)malloc(NDATA*sizeof(double));

    int i,j,k,l;
    for(l = i = 0; i < n && l < N/2; i++)
        for(j = 0; j < n && l < N/2; j++)
            for(k = 0; k < n && l < N/2; k++){
                particle[l].r.x = i*L/n;
                particle[l].r.y = j*L/n;
                particle[l].r.z = k*L/n;
                particle[N/2+l].r.x = particle[l].r.x + L/(2*n);
                particle[N/2+l].r.y = particle[l].r.y + L/(2*n);
                particle[N/2+l].r.z = particle[l].r.z + L/(2*n);
                l++;
            }

    vec3 tmp = vec3_new(0.0, 0.0, 0.0);
    for(k = 0; k < N; k++){
        particle[k].c = vec3_new(_rand(), _rand(), _rand());
        particle[k].v = vec3_new(_rand()*2-1, _rand()*2-1, _rand()*2-1);
        tmp.x += particle[k].v.x;
        tmp.y += particle[k].v.y;
        tmp.z += particle[k].v.z;
    }

    for(k = 0; k < N; k++){
        particle[k].v.x -= tmp.x/N;
        particle[k].v.y -= tmp.y/N;
        particle[k].v.z -= tmp.z/N;
    }
    double norm = 0;
    for(k = 0; k < N; k++)
        norm += vec3_dot(particle[k].v, particle[k].v);
    norm = sqrt( norm / (3 * N * temperature) );
    for(k = 0; k < N; k++){
        particle[k].v.x /= norm;
        particle[k].v.y /= norm;
        particle[k].v.z /= norm;
    }

    reset();
}

void run(){
    int i,j;
    int dx,dy,dz;
    double dv;
    vec3 dr;
    for(i = 0; i < N; i++)
        for(j = i+1; j != i; j = (j+1)%N)
            for(dx = -1; dx <= 1; dx++)
                for(dy = -1; dy <= 1; dy++)
                    for(dz = -1; dz <= 1; dz++){
                        dr.x = dx*L + particle[j].r.x - particle[i].r.x;
                        dr.y = dy*L + particle[j].r.y - particle[i].r.y;
                        dr.z = dz*L + particle[j].r.z - particle[i].r.z;
                        dv = -2 * (2 * pow(1 / vec3_mod(dr), 13) - pow(1 / vec3_mod(dr), 7)) * dt / vec3_mod(dr);
                        particle[i].v.x += dr.x * dv;
                        particle[i].v.y += dr.y * dv;
                        particle[i].v.z += dr.z * dv;
                    }

    for(i = 0; i < N; i++){
        particle[i].r.x += particle[i].v.x * dt;
        particle[i].r.y += particle[i].v.y * dt;
        particle[i].r.z += particle[i].v.z * dt;

        particle[i].r.x -= L * floor(particle[i].r.x / L);
        particle[i].r.y -= L * floor(particle[i].r.y / L);
        particle[i].r.z -= L * floor(particle[i].r.z / L);
    }

    for(i = 0; i < N; i++){
        for(j = i+1; j != i; j = (j+1)%N)
            for(dx = -1; dx <= 1; dx++)
                for(dy = -1; dy <= 1; dy++)
                    for(dz = -1; dz <= 1; dz++){
                        dr.x = dx*L + particle[j].r.x - particle[i].r.x;
                        dr.y = dy*L + particle[j].r.y - particle[i].r.y;
                        dr.z = dz*L + particle[j].r.z - particle[i].r.z;
                        dv = -2 * (2 * pow(1 / vec3_mod(dr), 13) - pow(1 / vec3_mod(dr), 7)) * dt / vec3_mod(dr);
                        particle[i].v.x += dr.x * dv;
                        particle[i].v.y += dr.y * dv;
                        particle[i].v.z += dr.z * dv;
                    }
    }

    runtime += dt;

    data[ptr = (ptr + 1) % NDATA] = get_temperature();
    if(abs(data[ptr]) > dmax) dmax = abs(data[ptr]); 
}

void print(){
    FILE *v = fopen("speed.dat","a");
    FILE *d = fopen("data.dat","w");

    int k;
    for(k = 0; k < N; k++){
        fprintf(v, "%e\t%e\t%e\n", particle[k].v.x, particle[k].v.y, particle[k].v.z);
    }
    for(k = ptr+1; k != ptr; k = (k+1)%NDATA){
        fprintf(d, "%e\n", data[k]);
    }

    fclose(v);
    fclose(d);
}

