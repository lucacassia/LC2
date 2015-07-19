#include "hardcore2d.h"

int main()
{
    ETA = 0.5;
    n_particles = 100;
    printf("\nparticles: %d\n\n",n_particles);
    printf("ETA = %f\n\n",ETA);
    init( ETA, 16.0f );

    /* thermalize */
    int t,k;
    for(t = 0; t < 10000; t++)
        run();

    /* collect data */
    for(t = 0; t < 10000; t++){
        for(k = 0; k < 500; k++)
            run();
        print_mom();
        if(!((t+1)%100))printf("Progress: %d%%\n",(t+1)/100);
    }

    clear();
    return 0;
}
