#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include"lib.h"

int main (int argc, char *argv[])
{
    rho = 0.7;
    NUMBER_OF_PARTICLES = 108;
    L = cbrt(NUMBER_OF_PARTICLES/rho);
    TEMPERATURE = 1.19;
    Rc = 2.5;
    Rm = 2.8;
    dF = -24*(2/pow(Rc,13)-1/pow(Rc,7));
    Uc = 4*(1/(pow(Rc,12))-1/(pow(Rc,6)));
    dt = 0.001;

    /* print header with infos */
    printf("#rho = %f N = %d L = %f T = %f dt = %f\n", rho, NUMBER_OF_PARTICLES, L, TEMPERATURE, dt );

    unsigned int step_MSD = 100;    /* step with which MSD measurements are taken */
    buffer_size = 300;              /* total number of measurements MSD */

    /* allocate memory */
    particleList = (body*)malloc(NUMBER_OF_PARTICLES * sizeof(body));
    neighboursList = malloc(NUMBER_OF_PARTICLES * NUMBER_OF_PARTICLES * sizeof(body));
    buffer = malloc(buffer_size * NUMBER_OF_PARTICLES * sizeof(body));

    init();
    PBC(particleList);
    print_coordinate();
    create_list();
    set_temperature(TEMPERATURE);

    /* thermalizartion */
    runtime = 0;
    int iteration = 0;
    printf("#t\tH\tP\n");
    while(iteration < 1e4){
        printf("%d\t%e\t%e\n", iteration*dt, total_energy(), total_momentum() );

        /* update list every 10 cycles */
        /*  and reset the temperature  */
        if(iteration%10 == 0){
            create_list();
            set_temperature(TEMPERATURE);
        }
        verlet(particleList);
        runtime += dt;
        iteration++;
    }

    /* measurements */
    runtime = 0;
    iteration = 0;
    int buffer_index = 0;
    printf("#i\tH\tP\n");
    while(iteration < buffer_size * step_MSD){
        if(iteration%1000 == 0){
            printf("%d\t%e\t%e\n", iteration, total_energy(), total_momentum() );
            print_distribution();
        }

        /* update list every 10 cycles */
        if(iteration%10==0){ create_list(); }

        verlet(particleList);
        runtime += dt;

        int i,j;
        if(iteration%step_MSD == 0){
            for(i = 0; i < NUMBER_OF_PARTICLES; i++)
                for(j = 0; j < DIMENSION; j++)
                    buffer[buffer_index * NUMBER_OF_PARTICLES + i] = particleList[i];
            buffer_index++;
        }
        if(iteration%20 == 0){
            print_energy();
            print_momentum();
        }
        iteration++;
    }

    /* compute the MSD */
    printf("# MSD saved to: data/MSD.dat\n");
    print_MSD("data/MSD.dat");

    /* free memory */
    free(particleList);
    free(neighboursList);
    free(buffer);

    return 0;
}
