#include "hardcore3d.h"

int main (int argc, char *argv[])
{
    int i, n_samples = 10;
    if(argc == 2){
        n_particles = atoi(argv[1]);
    }
    else{printf("usage: %s <n_particles>\n", argv[0] );return 1;}

    ETA = 0.3;
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
    sprintf(filename,"data/%.2f_TL.dat",ETA);
    FILE *file = fopen(filename,"a");
    x /= n_samples;
    err = sqrt((err/n_samples-x*x)/n_samples);
    fprintf(file, "%e\t%e\t%e\n", ETA, x, err );
    fclose(file);
    return 0;
}
