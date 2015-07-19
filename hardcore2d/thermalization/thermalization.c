#include "hardcore2d.h"

int main()
{
    n_particles = 100;
    double TEMP = 1.0;

    init(0.5,TEMP);
    print_pos();
    clear();

    /* N = 100 */

    printf("\nparticles: %d\n\n",n_particles);
    char filename[64];
    sprintf(filename,"data/thermalization_%d_%f.dat",n_particles,TEMP);
    FILE *f = fopen(filename,"w");
    int t;
    for(ETA = 0.1; ETA < 0.78; ETA += 0.02){
        printf("ETA = %f\n",ETA);
        init( ETA, TEMP );
        for(t = 0; t < 10000; t++){
            run();
            if(!(t%10))fprintf(f,"%e\t%d\t%e\t%e\n",ETA,t,get_pressure(),get_mean_free_path());
        }
        clear();
        fprintf(f,"\n");
    }
    fclose(f);

    /* N = 400 */
    n_particles = 400;
    printf("\nparticles: %d\n\n",n_particles);
    sprintf(filename,"data/thermalization_%d_%f.dat",n_particles,TEMP);
    f = fopen(filename,"w");
    for(ETA = 0.1; ETA < 0.78; ETA += 0.02){
        printf("ETA = %f\n",ETA);
        init( ETA, TEMP );
        for(t = 0; t < 10000; t++){
            run();
            if(!(t%10))fprintf(f,"%e\t%d\t%e\t%e\n",ETA,t,get_pressure(),get_mean_free_path());
        }
        clear();
        fprintf(f,"\n");
    }
    fclose(f);


    return 0;
}
