#include "hardcore2d.h"

int main (int argc, char *argv[])
{
    ETA = 0;
    if(argc==2){ETA = atof(argv[1]);}
    else{printf("usage: %s <ETA>\n", argv[0] );return 1;}

    n_particles = 100;

    printf("N = %d\tETA = %f\n", n_particles, ETA );
    init( ETA, 1.0f );
    int t;
    for(t = 0; t < 50000; t++){ run(); } /* thermalization */

    char filename[64];
    sprintf(filename,"data/%d_%.3f_mfp.dat",n_particles,ETA);
    FILE *file = fopen(filename,"a");
    double tmp, v[2][2]; int i,j;
    for(t = 0; t < 500000; t++){
        tmp = get_min_time();
        for(i = 0; i < 2; i++)for(j = 0; j < DIMENSION; j++)
            v[i][j] = particle[collider[i]].mom[j];
        fprintf(file, "%e\n%e\n", tmp*module(v[0]), tmp*module(v[1]) );
        run();
    }
    fclose(file);
    clear();
    return 0;
}
