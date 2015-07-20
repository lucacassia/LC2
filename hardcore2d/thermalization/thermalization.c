#include "hardcore2d.h"

int main()
{
    double TEMP = 1.0;
    char filename[64]; FILE *f; int t;

    for(n_particles = 100; n_particles <= 400; n_particles *= 4){
        for(ETA = 0.15; ETA < 0.78; ETA += 0.15){
            printf("\nN = %d\tETA = %f\n",n_particles,ETA);
            sprintf(filename,"data/%d_%f.dat",n_particles,ETA);
            f = fopen(filename,"w");
            init( ETA, TEMP );
            for(t = 0; t < 100000; t++){
                run();
                if(!(t%100))fprintf(f,"%e\t%d\t%e\t%e\t%e\n",ETA,t,get_pressure(),get_mean_free_path(),n_particles*runtime/(2*n_collisions));
            }
            clear();
            fclose(f);
        }
    }
    return 0;
}
