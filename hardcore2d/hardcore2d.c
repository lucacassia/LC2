/*
 * USAGE: ./hard_core_2d    <ETA> 
 *
 *   default ETA = 0.1f
 */

#define K_BOLTZ 1.0f

#include "hardcore2d.h"

int main (int argc, char *argv[])
{
    /* INIT VARI */
    /*Calcola il numero di istanti temporali che verranno salvati*/
    n_history = (int)(floor(TIME_MAX*1.0f/time_step)+1);
    unsigned int i;
    init();
    double dist_tot = 0.0f;
    double ETA = 0.1f;
    if(argc > 1) ETA = atof(argv[1]);

    SIGMA = 3.54490770181 * sqrt( ETA / (double)n_particles );

/*    DIST_RET = sqrt(4*0.74/ n_particles / M_PI);*/


    printf("\n\n*****************************************************\n");
    printf("Starting simulation with:\n");
    printf("SIGMA = %e\t",SIGMA);
    printf("Frazione di impacchettamento: %e\n", ETA);

    init();
    fix_boundaries();

    temperature = 2*get_kinetic()/((double) DIMENSION)/(double) n_particles/K_BOLTZ;
    printf(" K = %e \t P= %e \t", get_kinetic(), get_total_momentum());
    printf("Temperature is: %f \n",temperature );
    set_temperature(1.0f);
    temperature = 2*get_kinetic()/((double) DIMENSION)/(double) n_particles/K_BOLTZ;
    printf(" K = %e \t P= %e \t", get_kinetic(), get_total_momentum());
    printf("Temperature is: %f \n",temperature );

    /****** GESTIONE FILE  ******/
    char r2_file[64] = "";
    snprintf(r2_file,64,"data/dr2/dr2_%d_%.6lf.dat",(int)time(NULL),ETA); 
    /*char * press_file = "data/press.dat";*/
    char  tc_filename[64] = "";
    snprintf(tc_filename, 64, "data/tc/%d/tc%6f.dat",n_particles, ETA);

    char tcpdf_filename[64] = "";
    snprintf(tcpdf_filename, 64, "data/pdf_tc/%d/%6f.dat",n_particles, ETA);
    char mfp_filename[64] = "";
    snprintf(mfp_filename,64,"data/mfp/%d/mfp%.6lf.dat",n_particles,ETA);

    /****FINE GESTIONE FILE***/
    char  pressure_filename[128] = "";
    snprintf(pressure_filename,128,"data/pressure/%d/pressure%.6lf.dat",n_particles,ETA);


    print_pos();
    printf("#Collisions: %d \n", numOfCollisions);

    FILE *pdf_tc_file = fopen(tcpdf_filename,"w");

    /* Evolution */
    get_collision_table();
    while( numOfCollisions < THERMALIZATION_TIME ){ evolve_therm(); }

    numOfCollisions = 0;
    reset_mfp_variables();
    print_distribution();
    total_time = 0;
    pressure=0;
    printf("Termalizzato: %d urti ---- kin_en = %lf\n",numOfCollisions,get_kinetic());
    while(total_time < TIME_MAX){
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
    pressure /= (double) (3*(total_time)*get_kinetic());
    pressure *= SIGMA;
    pressure +=1.0;
    pressure *= (ETA/0.9069); /*dovuto a PV_0/NKT*/
    FILE *f_collision=fopen(tc_filename,"a");
    fprintf(f_collision,"%e\t%e\n",ETA,total_time/(2*numOfCollisions)*(n_particles));

    FILE * file_pressure = fopen(pressure_filename,"a");
    fprintf(file_pressure,"%e\n",pressure);
    fclose(file_pressure);

    FILE *f_mean_mfp = fopen( mfp_filename,"a");
    for(i = 0; i < n_particles; i++)
        dist_tot += particle[i].distance/(double)(particle[i].n_collisions); 

    dist_tot /= (double)(n_particles);
    fprintf(f_mean_mfp, "%.14e\t%.14e\t\n", ETA, dist_tot);
    fclose(f_mean_mfp);
    fclose(f_collision);
    clean();
    return 0;
}
