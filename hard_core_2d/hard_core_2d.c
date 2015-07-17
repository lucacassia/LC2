/*
 * USAGE: ./hard_core_2d    <eta> 
 *
 *   default eta = 0.1f
 */


#include "hard_core_2d.h"

int main (int argc, char *argv[])
{
    /* INIT VARI */
    /*Calcola il numero di istanti temporali che verranno salvati*/
    NUM_TEMPI_SALVATI = (int)(floor( (double) TIME_MAX / DeltaT)+1);
    unsigned int i;
    init();
    double dist_tot = 0.0f;
    double fraz_imp = 0.1f;
    if(argc > 1) fraz_imp = atof(argv[1]);

    SIGMA = sqrt(4*fraz_imp/ n_particles / M_PI);
    /* DA dove salta fuori?*/
    DIST_RET = sqrt(4*0.74/ n_particles / M_PI);
    printf("\n\n*****************************************************\n");
    printf("Starting simulation with:\n");
    printf("SIGMA = %e\t",SIGMA);
    printf("Frazione di impacchettamento: %e\n", fraz_imp);
    collTable = malloc (n_particles*n_particles*sizeof(double));
    particle = malloc ( n_particles * sizeof(body));
    time_list = malloc (NUM_TEMPI_SALVATI*n_particles * sizeof(body));
    set_pos();
    fix_boundaries();

    if ( check_distance() != 0 ){
        printf("Sfere troppo vicine tra loro. Avvio annullato\n");
        exit(EXIT_FAILURE);
    }

    temperature = 2*kin_en()/((double) DIMENSION)/(double) n_particles/K_BOLTZ;
    printf(" K = %e \t P= %e \t", kin_en(), total_momentum());
    printf("Temperature is: %f \n",temperature );
    riscala_vel_temp();
    temperature = 2*kin_en()/((double) DIMENSION)/(double) n_particles/K_BOLTZ;
    printf(" K = %e \t P= %e \t", kin_en(), total_momentum());
    printf("Temperature is: %f \n",temperature );

    /****** GESTIONE FILE  ******/
    char r2_file[64] = "";
    snprintf(r2_file,64,"data/dr2/dr2_%d_%.6lf.dat",(int)time(NULL),fraz_imp); 
    /*char * press_file = "data/press.dat";*/
    char  tc_filename[64] = "";
    snprintf(tc_filename, 64, "data/tc/%d/tc%6f.dat",n_particles, fraz_imp);

    char tcpdf_filename[64] = "";
    snprintf(tcpdf_filename, 64, "data/pdf_tc/%d/%6f.dat",n_particles, fraz_imp);
    char mfp_filename[64] = "";
    snprintf(mfp_filename,64,"data/mfp/%d/mfp%.6lf.dat",n_particles,fraz_imp);

    /****FINE GESTIONE FILE***/
    char  pression_filename[128] = "";
    snprintf(pression_filename,128,"data/pression/%d/pression%.6lf.dat",n_particles,fraz_imp);


    print_pos();
    printf("#Collisions: %d \n", numOfCollisions);

    FILE *pdf_tc_file = fopen(tcpdf_filename,"w");

    /* Evolution */
    collision_table();
    while( numOfCollisions < THERMALIZATION_TIME ){ evolve_therm(); }

    numOfCollisions = 0;
    reset_mfp_variables();
    print_distribution();
    total_time = 0;
    pression=0;
    printf("Termalizzato: %d urti ---- kin_en = %lf\n",numOfCollisions,kin_en());
    while(total_time < TIME_MAX){
        evolve();
        fprintf(pdf_tc_file,"%lf\n",time_collision*n_particles/2.0);
    }
    printf("Num collisioni: %d\n",numOfCollisions);
    fclose(pdf_tc_file);
    if(time_counted > NUM_TEMPI_SALVATI){
        printf("ERROR \n");
    }
    r_squared_save(r2_file);

    /****** CALCOLO PV/NKT = 1 + 1/(3*n_particles*k_boltz*temp)*massa*diametro*Somma collisioni******/
    pression /= (double) (3*(total_time)*kin_en());
    pression *= SIGMA;
    pression +=1.0;
    pression *= (fraz_imp/0.9069); /*dovuto a PV_0/NKT*/
    FILE *f_collision=fopen(tc_filename,"a");
    fprintf(f_collision,"%e\t%e\n",fraz_imp,total_time/(2*numOfCollisions)*(n_particles));

    FILE * file_pression = fopen(pression_filename,"a");
    fprintf(file_pression,"%e\n",pression);
    fclose(file_pression);

    FILE *f_mean_mfp = fopen( mfp_filename,"a");
    for(i = 0; i < n_particles; i++)
        dist_tot += particle[i].distance/(double)(particle[i].n_collision); 

    dist_tot /= (double)(n_particles);
    fprintf(f_mean_mfp, "%.14e\t%.14e\t\n", fraz_imp, dist_tot);
    fclose(f_mean_mfp);
    fclose(f_collision);
    free(particle);
    free(collTable);
    free(time_list);
    return 0;
}
