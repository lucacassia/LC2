#include "hardcore3d.h"

int main (int argc, char *argv[])
{
    int i, n_samples;
    ETA = 0.5;
    if(argc == 3){
        ETA = atof(argv[1]);
        n_samples = atoi(argv[2]);
    }
    else{printf("usage: %s <ETA> <n_samples>\n", argv[0] );return 1;}

    n_particles = 250;

    double tmp, x = 0.0f, err = 0.0f;
    printf("\nDIMENSION = %d\n\n", DIMENSION );
    printf("N = %d\tETA = %f\n", n_particles, ETA );
    for(i = 0; i < n_samples; i++){
        init( ETA, 1.0f );
        int t;for(t = 0; t < 50000; t++){ run(); if(t == 10000) reset(); } /* thermalization */
        /* pressure */
        tmp = SIGMA*dp/(2*get_kinetic_energy()*runtime);
        x += tmp;
        err += tmp*tmp;
    }

    char filename[64];
    sprintf(filename,"data/%d_multi.dat",n_particles);
    FILE *file = fopen(filename,"a");
    x /= n_samples;
    err = sqrt((err/n_samples-x*x)/n_samples);
    fprintf(file, "%e\t%e\t%e\n", ETA, x, err );
    fclose(file);
    return 0;
}
