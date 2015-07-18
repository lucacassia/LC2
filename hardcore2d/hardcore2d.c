/*
 * USAGE: ./hardcore2d  <ETA> 
 */

#include "hardcore2d.h"

#define THERMALIZATION_TIME 10000    /* number of collisions to thermalization */

int main (int argc, char *argv[])
{
    double ETA = 0.1f;
    if(argc > 1) ETA = atof(argv[1]);

    /* initialize and abort if disks dont fit the box */
    if(init(ETA, 1.0f)) return 1;

    printf("Starting simulation:\n");
    printf(" σ = %e\n", SIGMA);
    printf(" η = %e\n\n", ETA);

    print_pos();
    print_mom();

    set_temperature(5.0f);
    printf(" K = %e\tP = %e\tT = %e\n", get_kinetic_energy(), get_total_momentum(), get_temperature() );

    while( n_collisions < THERMALIZATION_TIME ) run();
    printf("Mixed for %d hits  ---->  K = %f\n", n_collisions, get_kinetic_energy() );
    print_distribution();

    reset_variables();

    char filename[128];
    FILE *f;

    /* tcpdf */
    sprintf(filename, "data/pdf_tc/%d/%f.dat", n_particles, ETA);
    f = fopen(filename,"w");
    while(runtime < n_history * time_step)
        fprintf(f, "%e\n", n_particles * run() / 2.0f);
    fclose(f);

    printf("Number of collisions: %d\n", n_collisions);

    if(idx_history_time > n_history)
        printf("ERROR \n");

    /* <dr²> */
    sprintf(filename, "data/dr2/dr2_%d_%f.dat", (int)time(NULL), ETA); 
    print_dr2(filename);

    /* collision times */
    sprintf(filename, "data/tc/%d/tc%f.dat", n_particles, ETA);
    f = fopen(filename,"a");
    fprintf(f, "%e\t%e\n", ETA, runtime/(2*n_collisions)*(n_particles));
    fclose(f);

    /* pressure */
    sprintf(filename, "data/pressure/%d/pressure%f.dat", n_particles, ETA);
    f = fopen(filename,"a");
    fprintf(f,"%e\n", get_pressure() * (ETA/0.9069) );
    fclose(f);

    /* mean free path */
    sprintf(filename, "data/mfp/%d/mfp%f.dat", n_particles, ETA);
    f = fopen(filename,"a");
    int i;
    double mean_free_path = 0.0f;
    for(i = 0; i < n_particles; i++)
        mean_free_path += particle[i].distance / particle[i].n_collisions; 
    mean_free_path /= n_particles;
    fprintf(f, "%e\t%e\t\n", ETA, mean_free_path);
    fclose(f);

    clean();
    return 0;
}
