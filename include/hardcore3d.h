#ifndef HARDCORE3D
#define HARDCORE3D

#define DIMENSION 3

#include "hardcore.h"

double get_collision_time(int i, int j)
{
    int k;
    double dr[DIMENSION], dv[DIMENSION], dx[DIMENSION];
    double t, rr, rv, vv, delta, collision_time = DBL_MAX;

    for(dx[0] = -1; dx[0] <= 1 ; dx[0]++){
        for(dx[1] = -1; dx[1] <= 1; dx[1]++){
            for(dx[2] = -1; dx[2] <= 1 ; dx[2]++){
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
    }
    return collision_time;
}

double get_sigma(double eta)
{
    double sigma = 1.240700981798800033336013624095556334701572400372003240197913 * cbrt(ETA/n_particles);
    /* check if disks fit the box */
    int k = 0; while( 2* k * k * k < n_particles ) k++;
    if( sigma > 0.866025403784438646763723170752936183471402626905190314027903 / k ) return -1;
    else return sigma;
}

/* BCC initialization */
void set_position()
{
    int n = 0; while(2 * n * n * n < n_particles ) n++;
    int i,j,k,l;
    for(l = i = 0; i < n && l < n_particles/2; i++)
        for(j = 0; j < n && l < n_particles/2; j++)
            for(k = 0; k < n && l < n_particles/2; k++){
                particle[l].pos[0] = i*1.0/n;
                particle[l].pos[1] = j*1.0/n;
                particle[l].pos[2] = k*1.0/n;
                particle[n_particles/2+l].pos[0] = 1.0/n/2.0 + i*1.0/n;
                particle[n_particles/2+l].pos[1] = 1.0/n/2.0 + j*1.0/n;
                particle[n_particles/2+l].pos[2] = 1.0/n/2.0 + k*1.0/n;
                l++;
            }
}

/* compute <dr²(dt)> by averaging on every particle at t,dt fixed. for each particle take the distance with its nearest copy */

double get_dr2(double **list0, double **list1)
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

double run()
{
    min_time = get_min_time();

    int i,j,k;

    if(!FULL_BUFFER_FLAG){
        while( idx * time_step < runtime + min_time){
            for(i = 0; i < n_particles; i++)
                for(j = 0; j < DIMENSION; j++){
                    buffer[idx][i][j] = particle[i].pos[j]+particle[i].mom[j] * ( idx * time_step - runtime );
                    buffer[idx][i][j] -= floor(buffer[idx][i][j]);
                }
            idx++;
            FULL_BUFFER_FLAG = !(idx < buffer_size);
        }
    }else FULL_BUFFER_FLAG = 1;


    for(k = 0; k < 2; k++){
        particle[collider[k]].distance += (runtime + min_time - particle[collider[k]].last_collision_time) * module(particle[collider[k]].mom);
        particle[collider[k]].last_collision_time = runtime + min_time;
        particle[collider[k]].n_collisions++;
    }

    double dr[DIMENSION], dv[DIMENSION], tmp[DIMENSION];

    for(j = 0; j < DIMENSION; j++){
        for(i = 0; i < n_particles; i++){
            particle[i].pos[j] += particle[i].mom[j] * min_time;
            particle[i].pos[j] -= floor(particle[i].pos[j]);
        }
        dr[j] = particle[collider[1]].pos[j] - particle[collider[0]].pos[j];
    }

    double dx, dy, dz;
    for(dx = -1; dx <= 1 ; dx++){
        for(dy = -1; dy <= 1; dy++){
            for(dz = -1; dz <= 1; dz++){
                tmp[0] = dx + particle[collider[1]].pos[0] - particle[collider[0]].pos[0];
                tmp[1] = dy + particle[collider[1]].pos[1] - particle[collider[0]].pos[1];
                tmp[2] = dz + particle[collider[1]].pos[2] - particle[collider[0]].pos[2];

                if(scalar(tmp,tmp) < scalar(dr,dr)){
                    dr[0] = tmp[0];
                    dr[1] = tmp[1];
                    dr[2] = tmp[2];
                }
            }
        }
    }
/*
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
*/
    for(j = 0; j < DIMENSION; j++)
        dv[j] = particle[collider[0]].mom[j] - particle[collider[1]].mom[j];

    for(j = 0; j < DIMENSION; j++){
        tmp[j] = scalar(dv,dr)*dr[j]/scalar(dr,dr);
        particle[collider[0]].mom[j] -= tmp[j];
        particle[collider[1]].mom[j] += tmp[j];
    }

    update_collision_table();

    n_collisions++;
    runtime += min_time;
    dp += module(dv);
    return min_time;
}

#endif
