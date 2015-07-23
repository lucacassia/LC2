#ifndef HARDCORE2D
#define HARDCORE2D

#define DIMENSION 2

#include "hardcore.h"

double get_table_entry(int i, int j)
{
    int k;
    double dr[DIMENSION], dv[DIMENSION], dx[DIMENSION];
    double t, rr, rv, vv, delta, collision_time = DBL_MAX;

    for(dx[0] = -1; dx[0] <= 1 ; dx[0]++){
        for(dx[1] = -1; dx[1] <= 1; dx[1]++){
            for(k = 0; k < DIMENSION; k++){
                dr[k] = dx[k] + particle[j].pos[k] - particle[i].pos[k];
                dv[k] = particle[j].mom[k] - particle[i].mom[k];
            }
            rr = scalar(dr, dr);
            rv = scalar(dr, dv);
            vv = scalar(dv, dv);
            delta = rv*rv-vv*(rr-SIGMA*SIGMA);

            if((rv < 0)&&(delta > 0)){
                t = (-rv-sqrt(delta))/vv;
                if(t < collision_time)
                    collision_time = t;
                }
        }
    }
    return collision_time;
}

void get_table()
{
    int i, j;
    collider[0] = 0;
    collider[1] = 1;
    double minimum = DBL_MAX;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++){
            table[i][j] = get_table_entry(i,j);
            if(table[i][j] <= minimum){
                minimum = table[i][j];
                collider[0] = i;
                collider[1] = j;
            }
        }
}

void update_table()
{
    int i, j;
    for(i = 0; i < n_particles; i++)
        for(j = i+1; j < n_particles; j++)
            if(i == collider[0] || j == collider[0] || i == collider[1] || j == collider[1])
                table[i][j] = get_table_entry(i,j);
            else
                table[i][j] -= min_time;
}

double get_params(double eta)
{
    ETA = eta;
    double sigma = 1.1283791671 * sqrt( ETA/n_particles );
    /* check if disks fit the box */
    int k = 0; while( k * k < n_particles ) k++;
    if( sigma > 1.0f / k ) return -1;
    else return SIGMA = sigma;
}

/* square packing initialization in 2d */
void set_position()
{
    int i, k = 0; while( k * k < n_particles ) k++;
    for(i = 0; i < n_particles; i++){
        /* place disks on a square lattice */
        particle[i].pos[0] = (0.5f/k)+(i%k)*(1.0f/k);
        particle[i].pos[1] = (0.5f/k)+(i/k)*(1.0f/k);
    }
}

/* compute <dr²(dt)> by averaging on every particle at t,dt fixed. for each particle take the distance with its nearest copy */
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
                for(j = 0; j < DIMENSION; j++)
                    dr[j] = dx[j] + list1[i][j] - list0[i][j];
                if(scalar(dr,dr) < distance)
                    distance = scalar(dr,dr);
            }
        sum += distance;
    }
    return sum / n_particles;
}

double run()
{
    min_time = get_min_time();

    int i,j,k;

    if(!FULL_BUFFER_FLAG){
        while( idx * time_step < runtime + min_time){
            for(i = 0; i < n_particles; i++)
                for(j = 0; j < DIMENSION; j++){
                    if(UNFOLD_FLAG)
                        buffer[idx][i][j] = particle[i].unf[j]+particle[i].mom[j] * ( idx * time_step - runtime );
                    else{
                        buffer[idx][i][j] = particle[i].pos[j]+particle[i].mom[j] * ( idx * time_step - runtime );
                        buffer[idx][i][j] -= floor(buffer[idx][i][j]);
                    }
                }
            idx++;
            FULL_BUFFER_FLAG = !(idx < buffer_size);
        }
    }


    for(k = 0; k < 2; k++){
        particle[collider[k]].distance += (runtime + min_time - particle[collider[k]].last_collision_time) * module(particle[collider[k]].mom);
        particle[collider[k]].last_collision_time = runtime + min_time;
        particle[collider[k]].n_collisions++;
    }

    double dr[DIMENSION], dv[DIMENSION], tmp[DIMENSION];

    for(j = 0; j < DIMENSION; j++){
        for(i = 0; i < n_particles; i++){
            particle[i].pos[j] += particle[i].mom[j] * min_time;
            particle[i].unf[j] += particle[i].mom[j] * min_time;
            particle[i].pos[j] -= floor(particle[i].pos[j]);
        }
        dr[j] = particle[collider[1]].pos[j] - particle[collider[0]].pos[j];
    }

    double dx[DIMENSION];
    for(dx[0] = -1; dx[0] <= 1 ; dx[0]++){
        for(dx[1] = -1; dx[1] <= 1; dx[1]++){
            for(j = 0; j < DIMENSION; j++)
                tmp[j] = dx[j] + particle[collider[1]].pos[j] - particle[collider[0]].pos[j];

            if(scalar(tmp,tmp) < scalar(dr,dr)){
                for(j = 0; j < DIMENSION; j++)
                    dr[j] = tmp[j];
            }
        }
    }

    for(j = 0; j < DIMENSION; j++)
        dv[j] = particle[collider[0]].mom[j] - particle[collider[1]].mom[j];

    for(j = 0; j < DIMENSION; j++){
        tmp[j] = scalar(dv,dr)*dr[j]/scalar(dr,dr);
        particle[collider[0]].mom[j] -= tmp[j];
        particle[collider[1]].mom[j] += tmp[j];
    }

    update_table();

    n_collisions++;
    runtime += min_time;
    dp += module(dv);
    return min_time;
}

#endif
