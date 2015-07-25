/*
 *  usage: ./thermalization > output
 */

#define DIMENSION 3

#include"softcore.h"

int main()
{
    /* MD settings */
    int N = 108;                                /* number of particles         */
    double rho = 0.7;                           /* density rho=(N*sigma^d)/L^d */
    L = pow(N/rho, 1.0f/DIMENSION);             /* box size                    */
    rc = 2.5;                                   /* cutoff radius               */
    rm = rc + 0.3;                              /* list cutoff radius          */
    dF = -24*(2/pow(rc,13)-1/pow(rc,7));        /* force at the cutoff         */
    Uc = 4*(1/(pow(rc,12))-1/(pow(rc,6)));      /* potential at the cutoff     */

    int total_steps = 5e4;                      /* toral number of time steps  */
    dt = 0.001;                                 /* time step length            */

    /* allocate memory */
    obj *particle = (obj*)malloc(N*sizeof(obj));
    int **neighbour = NULL;
    neighbour = create_table(neighbour,N);

    init_pos(particle,N/2,0.0);          /* BCC lattice           */
    init_pos(&particle[N/2],N-N/2,0.5);

    init_mom(particle,N);                /* initialize momenta    */
    reset_mom(particle,N,1.19/T);        /* set temperature T     */
    compute_table(particle,neighbour,N); /* table of neighbours   */
    get_acc(particle,neighbour,N);       /* compute accelerations */

    /* print header */
    printf("#N=%d rho=%f L=%f T=%f dt=%f\n", N, rho, L, T, dt);

    /* simulation run */
    int i;
    for(i = 0; i < total_steps; i++){
        if(!(i%10)) compute_table(particle,neighbour,N);    /* update table every 10 steps           */
        integrate(particle,neighbour,N);                    /* verlet velocity                       */
        if(i*dt<10) reset_mom(particle,N,1.19/T);           /* keep resetting T until thermalization */
        printf("%e %e %e %e %e\n", i*dt, H/N, U/N, K/N, T);
    }

    /* exit */
    free(particle);
    destroy_table(neighbour,N);
    return 0;
}
