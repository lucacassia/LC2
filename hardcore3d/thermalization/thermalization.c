#include "hardcore3d.h"

int main()
{
    char filename[64]; FILE *f; int t;
    printf("\nDIMENSION = %d\n",DIMENSION);
    n_particles = 128;
    for(ETA = 0.25; ETA < 0.68; ETA += 0.1){
        printf("\nN = %d\tETA = %f\n",n_particles,ETA);
        sprintf(filename,"data/%d_%f.dat",n_particles,ETA);
        f = fopen(filename,"w");
        init( ETA, 1.0 );
        for(t = 0; t < 100000; t++){
            run();
            if(!(t%100))fprintf(f,"%e\t%d\t%e\t%e\t%e\n",ETA,t,get_pressure(),get_mean_free_path(),n_particles*runtime/(2*n_collisions));
        }
        clear();
        fclose(f);
    }
    return 0;
}
