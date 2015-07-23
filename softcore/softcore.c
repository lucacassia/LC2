/*
 *  usage: ./softcore < input > output
 */

#define DIMENSION 3

#include"softcore.h"

int main()
{
   /* read parameters */
   fflush(stdout);
   scanf("%d", &n_particles);
   fflush(stdout);
   scanf("%lf", &rho);
   fflush(stdout);
   scanf("%lf", &T);
   fflush(stdout);
   scanf("%lf", &runtime);
   fflush(stdout);
   scanf("%lf", &time_step);
   fflush(stdout);
   scanf("%lf", &thermalization_time);

    L = cbrt(n_particles/rho);

    /* print header */
    printf("#N=%d L=%f T=%f runtime=%f dt=%f thermalization=%f\n", n_particles, L, T, runtime, time_step, thermalization_time);

    int numSteps = (int)(runtime/time_step + 0.5);
    int burninSteps = (int)(thermalization_time/time_step + 0.5);    
    int count;             /* counts time steps */
    int numPoints = 0;  /* counts measurements */
    double sumH = 0;  /* total energy accumulated over steps */
    double sumH2 = 0;  /* total energy squared accumulated */
    double avgH, avgH2, fluctH;  /* average energy, square, fluctuations */

    /* initialization */
    body *particle = (body*)malloc(n_particles*sizeof(body));
    init(particle);
    printf("#   time           E             U            K            T        <[H-<H>]²>\n");
    printf("%e %e %e %e %e %e\n", 0.0, H/n_particles, U/n_particles, K/n_particles, T, 0.0);

    FILE*f = fopen("trajectory.dat","w");

    /* thermalization */
    for(count = 0; count < burninSteps; count++){
        integrate(particle);

        fprintf(f,"%e\t%e\t%e\ti\n",PBC(particle[0].pos[0]),PBC(particle[0].pos[1]),PBC(particle[0].pos[2]));
        printf("%e %e %e %e %e %e\n", count*time_step, H/n_particles, U/n_particles, K/n_particles, T, 0.0);
    }

    /* collect data */
    for(count = burninSteps; count < numSteps; count++){
        integrate(particle);
        fprintf(f,"%e\t%e\t%e\ti\n",PBC(particle[0].pos[0]),PBC(particle[0].pos[1]),PBC(particle[0].pos[2]));

        /* accumulate energy and its square */
        sumH  = sumH + H;
        sumH2 = sumH2 + H*H;
        numPoints++;

        /* determine averages and fluctuations */
        avgH    = sumH/numPoints;
        avgH2  = sumH2/numPoints;
        fluctH = sqrt(avgH2 - avgH*avgH);

        printf("%e %e %e %e %e %e\n", count*time_step, H/n_particles, U/n_particles, K/n_particles, T, fluctH/n_particles);
    }
    fclose(f);

    clear(particle);

    return 0;
}
