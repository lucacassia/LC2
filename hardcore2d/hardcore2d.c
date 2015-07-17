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

    printf("\n\n*****************************************************\n");
    printf("Starting simulation with:\n");
    printf("SIGMA = %e\t", SIGMA);
    printf("ETA = %e\n", ETA);

    if(init()) return 1;
    double dist_tot = 0.0f;

    temperature = 2.0f * get_kinetic_energy() / (DIMENSION * n_particles);
    printf(" K = %e\tP = %e\t", get_kinetic_energy(), get_total_momentum() );
    printf("Temperature = %f\n", temperature );
    set_temperature(1.0f);
    temperature = 2.0f * get_kinetic_energy() / (DIMENSION * n_particles);
    printf(" K = %e\tP = %e\t", get_kinetic_energy(), get_total_momentum() );
    printf("Temperature = %f\n", temperature );

    /****** GESTIONE FILE  ******/
    char r2_file[64];
    sprintf(r2_file, "data/dr2/dr2_%d_%.6lf.dat", (int)time(NULL), ETA); 

    char  tc_filename[64];
    sprintf(tc_filename, "data/tc/%d/tc%6f.dat", n_particles, ETA);

    char tcpdf_filename[64];
    sprintf(tcpdf_filename, "data/pdf_tc/%d/%6f.dat", n_particles, ETA);

    char mfp_filename[64];
    sprintf(mfp_filename, "data/mfp/%d/mfp%.6lf.dat", n_particles, ETA);

    /****FINE GESTIONE FILE***/
    char pressure_filename[128];
    sprintf(pressure_filename, "data/pressure/%d/pressure%.6lf.dat", n_particles, ETA);

    print_pos();
    printf("Collisions = %d\n", numOfCollisions);

    FILE *pdf_tc_file = fopen(tcpdf_filename,"w");

    /* Evolution */
    while( numOfCollisions < THERMALIZATION_TIME ){ evolve_therm(); }

    reset_variables();
    print_distribution();
    printf("Termalizzato: %d urti ---- kin_en = %lf\n",numOfCollisions,get_kinetic_energy());
    while(total_time < n_history * time_step){
        evolve();
        fprintf(pdf_tc_file,"%lf\n",min_time*n_particles/2.0);
    }
    printf("Num collisioni: %d\n",numOfCollisions);
    fclose(pdf_tc_file);
    if(time_counted > n_history){
        printf("ERROR \n");
    }
    r_squared_save(r2_file);

    /****** CALCOLO PV/NKT = 1 + 1/(3*n_particles*k_boltz*temp)*massa*diametro*Somma collisioni******/
    pressure /= 3.0f * total_time * get_kinetic_energy();
    pressure *= SIGMA;
    pressure += 1.0f;
    pressure *= (ETA/0.9069); /*dovuto a PV_0/NKT*/
    FILE *f_collision = fopen(tc_filename,"a");
    fprintf(f_collision,"%e\t%e\n",ETA,total_time/(2*numOfCollisions)*(n_particles));

    FILE * file_pressure = fopen(pressure_filename,"a");
    fprintf(file_pressure,"%e\n",pressure);
    fclose(file_pressure);

    FILE *f_mean_mfp = fopen( mfp_filename,"a");
    int i;
    for(i = 0; i < n_particles; i++)
        dist_tot += particle[i].distance / particle[i].n_collisions; 

    dist_tot /= (n_particles);
    fprintf(f_mean_mfp, "%.14e\t%.14e\t\n", ETA, dist_tot);
    fclose(f_mean_mfp);
    fclose(f_collision);
    clean();
    return 0;
}
