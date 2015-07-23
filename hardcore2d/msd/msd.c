#include "hardcore2d.h"

int main (int argc, char *argv[])
{
    double total_time;
    if(argc == 5){
        ETA = atof(argv[1]);
        buffer_size = atoi(argv[2]);
        total_time = atof(argv[3]);
        UNFOLD_FLAG = atof(argv[4]);
    }else{
        printf("usage: %s <ETA> <buffer_size> <total_time> <UNFOLD_FLAG>\n", argv[0] );
        return 1;
    }

    time_step = total_time / buffer_size;
    n_particles = 100;
    printf("\nDIMENSION = %d\n\n", DIMENSION );
    printf("N = %d\tETA = %f", n_particles, ETA );
    if(UNFOLD_FLAG) printf("\t[UNFOLDED]\n\n" );
    else printf("\n\n");

    init( ETA, 1.0f );
    int t;for(t = 0; t < 50000; t++){ run(); } /* thermalization */
    printf("Thermalized\n");
    reset();

    /* trajectory */
    char filename[64];
    sprintf(filename, "data/position_%d_%d_%f.dat",n_particles/2, n_particles, ETA);
    FILE *f = fopen(filename,"w");
    while(idx < buffer_size){
        run(); int j;
        fprintf(f, "%e\t%e",ETA,runtime);
        for(j = 0; j < DIMENSION; j++)
            fprintf(f, "\t%e", particle[n_particles/2].pos[j]);
        for(j = 0; j < DIMENSION; j++)
            fprintf(f, "\t%e", particle[n_particles/2].unf[j]);
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Data gathered\n");

    /* MSD */
    if(UNFOLD_FLAG) sprintf(filename,"data/%d_%.3f_unf_msd.dat",n_particles,ETA);
    else            sprintf(filename,"data/%d_%.3f_msd.dat",n_particles,ETA);
    printf("UF: %d\n",UNFOLD_FLAG);
    print_MSD(filename);

    clear();
    return 0;
}
