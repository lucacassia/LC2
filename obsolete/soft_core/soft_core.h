#ifndef SOFTCORE3D
#define SOFTCORE3D

#include <string.h>

#define DIMENSION 3

#include "hardcore.h"

double R_LIM;
double U_R_LIM;
double DeltaF;

double potential(double r)
{
    if(r > R_LIM) return 0;
    return (( 4*(1/(pow(r,12))-1/(pow(r,6)))) - U_R_LIM - DeltaF * (r - 0.25));
}

double force(double r)
{
    return (24*(2*pow(1/r,13) - pow(1/r,7))+ DeltaF);
}

double get_params(double density)
{
    if(density > 1) return -1; /* error code */
    SIGMA = 1.0f;

    R_LIM = 2.5 * SIGMA;
    U_R_LIM = 4*(1/(pow(R_LIM,12))-1/(pow(R_LIM,6)));
    DeltaF = -0.039;

    box_size = cbrt(n_particles/density);
    return box_size;
}

/* BCC initialization in 3d */
void set_position()
{
    int n = 0; while(2 * n * n * n < n_particles ) n++;
    int i,j,k,l;
    for(l = i = 0; i < n && l < n_particles/2; i++)
        for(j = 0; j < n && l < n_particles/2; j++)
            for(k = 0; k < n && l < n_particles/2; k++){
                particle[l].pos[0] = i*box_size/n;
                particle[l].pos[1] = j*box_size/n;
                particle[l].pos[2] = k*box_size/n;
                particle[n_particles/2+l].pos[0] = (0.5f+i)*box_size/n;
                particle[n_particles/2+l].pos[1] = (0.5f+j)*box_size/n;
                particle[n_particles/2+l].pos[2] = (0.5f+k)*box_size/n;
                l++;
            }
}

/* decides if particle i and j are close enough to interact */
double get_table_entry(int i, int j)
{
    double dx,dy,dz;
    double dr[DIMENSION];
    /* look in every box */
    for(dx = -box_size; dx <= box_size; dx += box_size)
        for(dy = -box_size; dy <= box_size; dy += box_size)
            for(dz = -box_size; dz <= box_size; dz += box_size){
                dr[0] = dx + particle[j].pos[0] - particle[i].pos[0];
                dr[1] = dy + particle[j].pos[1] - particle[i].pos[1];
                dr[2] = dz + particle[j].pos[2] - particle[i].pos[2];
                if(module(dr) < R_LIM+0.3*SIGMA)
                    return 1;
            }
    return 0;
}

/* fill neighbors table                                              */
/* table[i][0]   contains the number of neighbors of particle i      */
/* table[i][j+1] contains the index of the j-th neighbor particle i  */
/* i < table[i][j+1]    and    j < table[i][0]                        */
void get_table()
{
    int i,j,count;
    for(i = 0; i < n_particles; i++){
        count = 0;
        for(j = (i+1)%n_particles; j != i; j = (j+1)%n_particles)
            if(get_table_entry(i,j) == 1){
                table[i][count+1] = j;
                count++;
            }
        table[i][0] = count;
    }
}

void update_table()
{
    get_table();
}

/* velocity verlet integration algorithm */
double run(){
    int i,j,FOUND_FLAG;
    double dx,dy,dz;
    double r,dr[DIMENSION];

    get_table();

    /* compute acceleration a(t) = f(r(t))/m */
    for(i = 0; i < n_particles; i++){
        for(j = 0; j < DIMENSION; j++)
            particle[i].acc[j] = 0.0f;
        for(j = 0; j < table[i][0]; j++){
            FOUND_FLAG = 0;
            /* look in every box */
            for(dx = -box_size; dx <= box_size && !FOUND_FLAG; dx += box_size)
                for(dy = -box_size; dy <= box_size && !FOUND_FLAG; dy += box_size)
                    for(dz = -box_size; dz <= box_size && !FOUND_FLAG; dz += box_size){
                        dr[0] = dx + particle[(int)table[i][j+1]].pos[0] - particle[i].pos[0];
                        dr[1] = dy + particle[(int)table[i][j+1]].pos[1] - particle[i].pos[1];
                        dr[2] = dz + particle[(int)table[i][j+1]].pos[2] - particle[i].pos[2];
                        r = module(dr);
                        if(r < R_LIM){
                            for(j = 0; j < DIMENSION; j++)
                                particle[i].acc[j] += force(r)*dr[j]/r;
                            /* particle found => skip to next j-cycle */
                            FOUND_FLAG = 1;
                        }
                    }
        }
    }

    /* compute new position r(t+dt) = r(t) + v(t)dt + ½a(t)dt² */
    for(i = 0; i < n_particles; i++)
        for(j = 0; j < DIMENSION; j++){
            particle[i].unf[j] += particle[i].mom[j] * time_step + particle[i].acc[j] * time_step * time_step / 2;
            particle[i].pos[j] += particle[i].mom[j] * time_step + particle[i].acc[j] * time_step * time_step / 2;
            particle[i].pos[j] = fmod( fmod( particle[i].pos[j] , box_size ) + box_size, box_size );
            if(!FULL_BUFFER_FLAG){
                if(UNFOLD_FLAG) buffer[idx][i][j] = particle[i].unf[j];
                else buffer[idx][i][j] = particle[i].pos[j];
                idx++;
                FULL_BUFFER_FLAG = !(idx < buffer_size);
            }
        }

    /* compute new acceleration a(t+dt) = f(r(t+dt))/m */
    /* also compute total potential energy for every particle and store it in particle[i].distance */
    for(i = 0; i < n_particles; i++){
        particle[i].distance = 0.0f;
        for(j = 0; j < table[i][0]; j++){
            FOUND_FLAG = 0;
            /* look in every box */
            for(dx = -box_size; dx <= box_size && !FOUND_FLAG; dx += box_size)
                for(dy = -box_size; dy <= box_size && !FOUND_FLAG; dy += box_size)
                    for(dz = -box_size; dz <= box_size && !FOUND_FLAG; dz += box_size){
                        dr[0] = dx + particle[(int)table[i][j+1]].pos[0] - particle[i].pos[0];
                        dr[1] = dy + particle[(int)table[i][j+1]].pos[1] - particle[i].pos[1];
                        dr[2] = dz + particle[(int)table[i][j+1]].pos[2] - particle[i].pos[2];
                        r = module(dr);
                        if(r < R_LIM){
                            particle[i].distance += potential(r);
                            for(j = 0; j < DIMENSION; j++)
                                particle[i].acc[j] += force(r) * dr[j] / r;
                            /* particle found => skip to next j-cycle */
                            FOUND_FLAG = 1;
                        }
                    }
        }
        /* compute new momentum v(t+dt) = v(t) + ½(a(t)+a(t+dt))dt */
        for(j = 0; j < DIMENSION; j++)
            particle[i].mom[j] += 0.5f * particle[i].acc[j] * time_step;
    }

    runtime += time_step;
    return get_temperature();
}

double get_potential_energy(){
    double potential = 0.0;
    int i;
    for(i = 0; i < n_particles; i++)
        potential += particle[i].distance;
    return potential/2;
}

double get_MSD(double **list0, double **list1)
{
    int i,j;
    int dx[DIMENSION];
    double distance, sum = 0.0f;
    double dr[DIMENSION];
    for(i = 0; i < n_particles; i++){
        /* first copy */
        for(j = 0; j < DIMENSION; j++)
            dr[j] = list1[i][j] - list0[i][j];
        distance = scalar(dr,dr);
        /* check other copies */
        for(dx[0] = -1; dx[0] <= 1 ; dx[0]++)
            for(dx[1] = -1; dx[1] <= 1; dx[1]++){
                for(dx[2] = -1; dx[2] <= 1; dx[2]++){
                    for(j = 0; j < DIMENSION; j++)
                        dr[j] = dx[j] + list1[i][j] - list0[i][j];
                    if(scalar(dr,dr) < distance)
                        distance = scalar(dr,dr);
                }
            }
        sum += distance;
    }
    return sum / n_particles;
}

#endif
