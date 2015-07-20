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
    sprintf(filename,"data/%d_%.3f_times.dat",n_particles,ETA);
    FILE *file = fopen(filename,"a");
    for(t = 0; t < 1000000; t++)
        fprintf(file, "%e\n", run() );
    fclose(file);
    clear();
    return 0;
}
