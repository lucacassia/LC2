/*
 * USAGE: ./hardcore2d  <ETA> 
 */

#include "hardcore2d.h"

#define THERMALIZATION_TIME 10000    /* number of collisions to thermalization */

int main (int argc, char *argv[])
{
    double ETA = 0.1f;
    if(argc > 1) ETA = atof(argv[1]);

    SIGMA = 1.1283791671 * sqrt( ETA / n_particles );

    printf("\n*****************************************************\n");
    printf("Starting simulation:\n");
    printf(" σ = %e\n", SIGMA);
    printf(" η = %e\n", ETA);

    /* abort if disks dont fit the box */
    if(init()) return 1;

    printf(" K = %e\tP = %e\t", get_kinetic_energy(), get_total_momentum() );
    printf("Temperature = %f\n", get_temperature() );
    set_temperature(5.0f);
    printf(" K = %e\tP = %e\t", get_kinetic_energy(), get_total_momentum() );
    printf("Temperature = %f\n", get_temperature() );

    /****** GESTIONE FILE  ******/
    char r2_file[64];
    sprintf(r2_file, "data/dr2/dr2_%d_%f.dat", (int)time(NULL), ETA); 

    char  tc_filename[64];
    sprintf(tc_filename, "data/tc/%d/tc%f.dat", n_particles, ETA);

    char tcpdf_filename[64];
    sprintf(tcpdf_filename, "data/pdf_tc/%d/%f.dat", n_particles, ETA);

    char mfp_filename[64];
    sprintf(mfp_filename, "data/mfp/%d/mfp%f.dat", n_particles, ETA);

    char pressure_filename[128];
    sprintf(pressure_filename, "data/pressure/%d/pressure%f.dat", n_particles, ETA);
    /****FINE GESTIONE FILE***/

    print_pos();

    while( n_collisions < THERMALIZATION_TIME )
        thermalize();
    print_distribution();
    printf("Termalizzato: %d urti ---- kin_en = %f\n", n_collisions, get_kinetic_energy());
    reset_variables();


    FILE *f = fopen(tcpdf_filename,"w");
    while(total_time < n_history * time_step){
        evolve();
        fprintf(f,"%e\n", n_particles * min_time / 2.0f);
    }
    fclose(f);

    printf("Num collisioni: %d\n", n_collisions);
    if(time_counted > n_history)
        printf("ERROR \n");

    print_dr2(r2_file);

    /****** CALCOLO PV/NKT = 1 + 1/(3*n_particles*k_boltz*temp)*massa*diametro*Somma collisioni******/
    pressure /= 3.0f * total_time * get_kinetic_energy();
    pressure *= SIGMA;
    pressure += 1.0f;
    pressure *= (ETA/0.9069);

    f = fopen(tc_filename,"a");
    fprintf(f, "%e\t%e\n", ETA, total_time/(2*n_collisions)*(n_particles));
    fclose(f);

    f = fopen(pressure_filename,"a");
    fprintf(f,"%e\n",pressure);
    fclose(f);

    f = fopen(mfp_filename,"a");
    int i;
    double mean_free_path = 0.0f;
    for(i = 0; i < n_particles; i++)
        mean_free_path += particle[i].distance / particle[i].n_collisions; 
    mean_free_path /= n_particles;
    fprintf(f, "%.14e\t%.14e\t\n", ETA, mean_free_path);
    fclose(f);
    clean();
    return 0;
}
