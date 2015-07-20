#include "hardcore2d.h"

int main (int argc, char *argv[])
{
    ETA = 0;
    if(argc==2){ETA=atof(argv[1]);}
    else{printf("usage: %s <ETA>\n", argv[0] );return 1;}

    n_particles = 100;

    printf("N = %d\tETA = %f\n", n_particles, ETA );
    init( ETA, 1.0f );
    int t;for(t = 0; t < 50000; t++){ run(); if(t == 10000) reset(); } /* thermalization */

    char filename[64];
    sprintf(filename,"data/%d_single.dat",n_particles);
    FILE *file = fopen(filename,"a");
    fprintf(file, "%e\t%e\t%e\t%e\n", ETA, SIGMA*dp/(2*runtime*get_kinetic_energy()), get_mean_collision_time(), get_mean_free_path() );

    clear();

    fclose(file);
    return 0;
}
