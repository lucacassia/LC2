#include <string.h>
#include "vec3.h"

int N = 70;
double L = 3;
double dt = 1e-4;
body *particle = NULL;
int *list = NULL;

double temperature = 0;
int runtime;

int NDATA = 5000;
double *data = NULL;
vec3 *position = NULL;
int ptr = 0;

void clear(){
    if(particle != NULL)
        free(particle);
    if(list != NULL)
        free(list);
    if(data != NULL)
        free(data);
    if(position != NULL)
        free(position);
}

void reset(){
    runtime = 0;
}

double get_temperature(){
    double tmp = 0;
    int i;
    for(i = 0; i < N; i++)
        tmp += vec3_dot(particle[i].v, particle[i].v);
    return tmp / (3 * N);
}

double get_energy(){
    double tmp = 0;
    int i,j;
    double dx,dy,dz,dv;
    vec3 dr;
    for(i = 0; i < N; i++){
        tmp += vec3_dot(particle[i].v, particle[i].v);
        for(j = 0; j < list[i*N]; j++)
            for(dx = -L; dx <= L; dx += L)
                for(dy = -L; dy <= L; dy += L)
                    for(dz = -L; dz <= L; dz += L){
                        dr.x = dx + particle[list[i*N+j+1]].r.x - particle[i].r.x;
                        dr.y = dy + particle[list[i*N+j+1]].r.y - particle[i].r.y;
                        dr.z = dz + particle[list[i*N+j+1]].r.z - particle[i].r.z;
                        if(vec3_mod(dr) < 2.5){
                            dv = -2 * (2 * pow(1 / vec3_mod(dr), 13) - pow(1 / vec3_mod(dr), 7)) * dt / vec3_mod(dr);
                            particle[i].v.x += dr.x * dv;
                            particle[i].v.y += dr.y * dv;
                            particle[i].v.z += dr.z * dv;
                        }
                    }
    }
    return tmp / (3 * N);
}

void normalize(){
    int k;
    vec3 tmp = vec3_new(0.0, 0.0, 0.0);
    for(k = 0; k < N; k++){
        tmp.x += particle[k].v.x;
        tmp.y += particle[k].v.y;
        tmp.z += particle[k].v.z;
    }

    for(k = 0; k < N; k++){
        particle[k].v.x -= tmp.x/N;
        particle[k].v.y -= tmp.y/N;
        particle[k].v.z -= tmp.z/N;
    }
    double norm = sqrt( temperature / get_temperature() );
    for(k = 0; k < N; k++){
        particle[k].v.x *= norm;
        particle[k].v.y *= norm;
        particle[k].v.z *= norm;
    }
}

void init(){
    int n = 0;
    while(2*n*n*n < N) n++;

    clear();
    particle = (body*)malloc(N*sizeof(body));
    list = (int*)malloc(N*N*sizeof(int));
    data = (double*)malloc(NDATA*sizeof(double));
    position = (vec3*)malloc(NDATA*N*sizeof(vec3));

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

    for(k = 0; k < N; k++){
        particle[k].c = vec3_new(_rand(), _rand(), _rand());
        particle[k].v = vec3_new(_rand()*2-1, _rand()*2-1, _rand()*2-1);
        position[k] = particle[k].r;
    }

    normalize();
    reset();
}

void run(){
    int i,j,k;
    double dx,dy,dz,dv;
    vec3 dr;

    ptr = (ptr + 1) % NDATA;

    /* fill neighbors list*/
    if(!runtime%10)
        for(i = 0; i < N; i++){
            k = 0;
            for(j = i+1; j != i; j = (j+1)%N)
                for(dx = -L; dx <= L; dx += L)if(list[i*N+k] != j)
                    for(dy = -L; dy <= L && list[i*N+k] != j; dy += L)if(list[i*N+k] != j)
                        for(dz = -L; dz <= L && list[i*N+k] != j; dz += L)if(list[i*N+k] != j){
                            dr.x = dx + particle[j].r.x - particle[i].r.x;
                            dr.y = dy + particle[j].r.y - particle[i].r.y;
                            dr.z = dz + particle[j].r.z - particle[i].r.z;
                            if(vec3_mod(dr) < 2.8)
                                list[i*N+(++k)] = j;
                        }
            list[i*N] = k;
        }

    runtime++;

    /* verlet */
    for(i = 0; i < N; i++)
        for(j = 0; j < list[i*N]; j++)
            for(dx = -L; dx <= L; dx += L)
                for(dy = -L; dy <= L; dy += L)
                    for(dz = -L; dz <= L; dz += L){
                        dr.x = dx + particle[list[i*N+j+1]].r.x - particle[i].r.x;
                        dr.y = dy + particle[list[i*N+j+1]].r.y - particle[i].r.y;
                        dr.z = dz + particle[list[i*N+j+1]].r.z - particle[i].r.z;
                        if(vec3_mod(dr) < 2.5){
                            dv = -2 * (2 * pow(1 / vec3_mod(dr), 13) - pow(1 / vec3_mod(dr), 7)) * dt / vec3_mod(dr);
                            particle[i].v.x += dr.x * dv;
                            particle[i].v.y += dr.y * dv;
                            particle[i].v.z += dr.z * dv;
                        }
                    }

    for(i = 0; i < N; i++){
        particle[i].r.x += particle[i].v.x * dt;
        particle[i].r.y += particle[i].v.y * dt;
        particle[i].r.z += particle[i].v.z * dt;

        position[ptr*N+i].x = position[((NDATA+ptr-1)%NDATA)*N+i].x + particle[i].v.x * dt;
        position[ptr*N+i].y = position[((NDATA+ptr-1)%NDATA)*N+i].y + particle[i].v.y * dt;
        position[ptr*N+i].z = position[((NDATA+ptr-1)%NDATA)*N+i].z + particle[i].v.z * dt;

        particle[i].r.x -= L * floor(particle[i].r.x / L);
        particle[i].r.y -= L * floor(particle[i].r.y / L);
        particle[i].r.z -= L * floor(particle[i].r.z / L);
    }

    for(i = 0; i < N; i++)
        for(j = 0; j < list[i*N]; j++)
            for(dx = -L; dx <= L; dx += L)
                for(dy = -L; dy <= L; dy += L)
                    for(dz = -L; dz <= L; dz += L){
                        dr.x = dx + particle[list[i*N+j+1]].r.x - particle[i].r.x;
                        dr.y = dy + particle[list[i*N+j+1]].r.y - particle[i].r.y;
                        dr.z = dz + particle[list[i*N+j+1]].r.z - particle[i].r.z;
                        if(vec3_mod(dr) < 2.5){
                            dv = -2 * (2 * pow(1 / vec3_mod(dr), 13) - pow(1 / vec3_mod(dr), 7)) * dt / vec3_mod(dr);
                            particle[i].v.x += dr.x * dv;
                            particle[i].v.y += dr.y * dv;
                            particle[i].v.z += dr.z * dv;
                        }
                    }

    data[ptr] = get_temperature();
}

void get_dr2(){
    int i,j,k;
    double dr2[NDATA];
    vec3 dr;
    for(k = 1; k < NDATA; k++){
        dr2[k] = 0;
        for(i = ptr+1; i != (NDATA+ptr-k)%NDATA; i = (i+1)%NDATA){
            for(j = 0; j < N; j++){
                dr.x = position[((i+k)%NDATA)*N+j].x - position[i*N+j].x;
                dr.y = position[((i+k)%NDATA)*N+j].y - position[i*N+j].y;
                dr.z = position[((i+k)%NDATA)*N+j].z - position[i*N+j].z;
                dr2[k] += vec3_dot(dr,dr);
            }
        }
    }
    FILE *f = fopen("dr2.dat","w");
    for(k = 1; k < NDATA; k++)
        fprintf(f, "%d\t%e\n", k, dr2[k]/(N*(NDATA/k)) );
    fclose(f);
}

void print(){
    FILE *v = fopen("speed.dat","a");
    FILE *d = fopen("data.dat","w");
    FILE *p = fopen("pos.dat","w");

    int k;
    for(k = 0; k < N; k++){
        fprintf(v, "%e\t%e\t%e\n", particle[k].v.x, particle[k].v.y, particle[k].v.z);
    }
    for(k = ptr+1; k != ptr; k = (k+1)%NDATA){
        fprintf(d, "%e\n", data[k]);
    }

    for(k = ptr+1; k != ptr; k = (k+1)%NDATA){
        fprintf(p, "%e\t%e\t%e\n", position[k*N].x, position[k*N].y, position[k*N].z);
    }

    fclose(v);
    fclose(d);
    fclose(p);

    get_dr2();    
}

