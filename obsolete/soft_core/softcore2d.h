#ifndef SOFTCORE2D
#define SOFTCORE2D

#define DIMENSION 2

#include "softcore.h"

double potential(double r)
{
    if(r > R_C) return 0;
    return 4 * ( pow(1/r,12) - pow(1/r,6) ) - U_C + F_C * (r - R_C);
}

double force(double r)
{
    return 24 * ( 2 * pow(1/r,13) - pow(1/r,7) ) - F_C;
}

double PBC(double x)
{
    return fmod(fmod(x,box_size)+box_size,box_size);
}

/* compute accelerations */
void get_acc()
{
    int i,j,k;
    double r,dr[DIMENSION],fij;

    /* initialize energy and forces to zero */
    U = 0;

    for(i = 0; i < n_particles; i++)
        for(k = 0; k < DIMENSION; k++)
            particle[i].acc[k] = 0;

    /* determine interaction for each pair of particles (i,j) */
    for(i = 0; i < n_particles-1; i++){
        for(j = i+1; j < n_particles; j++){
            for(k = 0; k < DIMENSION; k++)
                dr[k] = PBC( particle[i].pos[k] - particle[j].pos[k] );
            r = module(dr);
            if( r < R_C ){
                fij = force(r);
                for(k = 0; k < DIMENSION; k++){
                    particle[i].pos[k] = particle[i].pos[k] + fij*dr[k];
                    particle[j].pos[k] = particle[j].pos[k] - fij*dr[k];
                }
                U += potential(r);
            }
        }
    }
}

/* velocity verlet */
void integrate()
{
    int i,k;
    /* compute intermediate momentum v(t+½dt) = v(t) + ½a(t)dt */
    for(i = 0; i < n_particles; i++)
        for(k = 0; k < DIMENSION; k++)
            particle[i].mom[k] += 0.5 * time_step * particle[i].acc[k];

    /* compute new position r(t+dt) = r(t) + v(t)dt + ½a(t)dt² */
    /*                              = r(t) + v(t+½dt)dt        */
    for(i = 0; i < n_particles; i++)
        for(k = 0; k < DIMENSION; k++)
            particle[i].pos[k] = PBC( particle[i].pos[k] + time_step * particle[i].mom[k] );

    /* compute new acceleration a(t+dt) = f(r(t+dt))           */
    get_acc();

    /* compute new momentum v(t+dt) = v(t) + ½(a(t)+a(t+dt))dt */
    K = 0;
    for(i = 0; i < n_particles; i++){
        for(k = 0; k < DIMENSION; k++)
            particle[i].mom[k] = particle[i].mom[k] + 0.5 * time_step * particle[i].acc[k];
        K += module(particle[i].mom)/2;
    }

    T = 2*K/(DIMENSION*n_particles);
    H = K + U;
}

/* square packing initialization in 2d */
void set_position()
{
    int i, k = 0; while( k * k < n_particles ) k++;
    for(i = 0; i < n_particles; i++){
        /* place disks on a square lattice */
        particle[i].pos[0] = (0.5f+i%k)*(box_size/k);
        particle[i].pos[1] = (0.5f+i/k)*(box_size/k);
    }

    /* also initialize acceleration */
    get_acc();
}

/* decide if particle i and j are close enough to interact */
int get_neighbor_entry(int i, int j)
{
    int k;
    double dr[DIMENSION];
    for(k = 0; k < DIMENSION; k++)
        dr[k] = PBC( particle[j].pos[k] - particle[i].pos[k] );
    if(module(dr) < R_C + 0.3) return 1;
    return 0;
}

/* compute the table of neighbors                                        */
/* neighbor[i][0]   contains the number of neighbors of particle i      */
/* neighbor[i][j+1] contains the index of the j-th neighbor particle i  */
void get_neighbor()
{
    int i,j;
    for(i = 0; i < n_particles; i++){
        neighbor[i][0] = 0;
        for(j = 0; j < n_particles; j++){
            if((i != j)&&(get_neighbor_entry(i,j) == 1)){
                neighbor[i][neighbor[i][0]+1] = j;
                neighbor[i][0]++;
            }
        }
    }
}

void run()
{
    /*get_neighbor();*/

    integrate();

    int i,k;
    if(!FULL_BUFFER_FLAG)
        for(i = 0; i < n_particles; i++)
            for(k = 0; k < DIMENSION; k++){
                if(UNFOLD_FLAG) buffer[idx][i][k] = particle[i].unf[k];
                           else buffer[idx][i][k] = particle[i].pos[k];
                idx++;
                FULL_BUFFER_FLAG = !(idx < buffer_size);
            }

    runtime += time_step;
    int_time++;
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
/*                for(dx[2] = -1; dx[2] <= 1; dx[2]++){*/
                    for(j = 0; j < DIMENSION; j++)
                        dr[j] = dx[j] + list1[i][j] - list0[i][j];
                    if(scalar(dr,dr) < distance)
                        distance = scalar(dr,dr);
/*                }*/
            }
        sum += distance;
    }
    return sum / n_particles;
}

#endif
