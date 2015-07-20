#include "hardcore2d.h"

int main (int argc, char *argv[])
{
    int i, n_samples = 10;
    ETA = 0.5;
    if(argc == 3){
        ETA = atof(argv[1]);
        n_samples = atoi(argv[2]);
    }
    else{printf("usage: %s <ETA> <n_samples>\n", argv[0] );return 1;}

    n_particles = 100;

    double tmp, x[3] = {0.0f}, err[3] = {0.0f};
    printf("N = %d\tETA = %f\n", n_particles, ETA );
    for(i = 0; i < n_samples; i++){
        init( ETA, 1.0f );
        int t;for(t = 0; t < 50000; t++){ run(); if(t == 10000) reset(); } /* thermalization */
        /* pressure */
        tmp = SIGMA*dp/(2*get_kinetic_energy()*runtime);
        x[0] += tmp;
        err[0] += tmp*tmp;
        /* collision times */
        tmp =  get_mean_collision_time();
        x[1] += tmp;
        err[1] += tmp*tmp;
        /* mean free path */
        tmp =  get_mean_free_path();
        x[2] += tmp;
        err[2] += tmp*tmp;
        clear();
    }

    char filename[64];
    sprintf(filename,"data/%d_multi.dat",n_particles);
    FILE *file = fopen(filename,"a");
    fprintf(file, "%e", ETA);
    for(i = 0; i < 3; i++){
        x[i] /= n_samples;
        err[i] = sqrt((err[i]/n_samples-x[i]*x[i])/n_samples);
        fprintf(file, "\t%e\t%e", x[i], err[i] );
    }
    fprintf(file, "\n" );
    fclose(file);
    return 0;
}
