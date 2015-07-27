/*
 *  usage: ./thermo_limit > output
 */

#define DIMENSION 3

#include"softcore.h"

int main(int argc, char *argv[])
{
    if(argc == 2) N = atoi(argv[1]);
    else return 1;

    /* MD settings */
    rho = 0.7;
    L = pow(N/rho, 1.0f/DIMENSION);
    double ENERGY = -2.98*N;

    int total_steps = 11e4;

    /* allocate memory */
    obj *particle = (obj*)malloc(N*sizeof(obj));
    int **neighbour = NULL;
    neighbour = create_table(neighbour);

    init_pos(particle,N/2,0.0);
    init_pos(&particle[N/2],N-N/2,0.5);

    init_mom(particle);
    reset_mom(particle, 1/T );
    compute_table(particle,neighbour);
    get_acc(particle,neighbour);

    /* print header */
    printf("#N=%d rho=%f L=%f T=%f dt=%f\n", N, rho, L, T, dt);
    printf("#\tt\tH\tU\tK\tT\n");

    double sumU = 0.0f;
    double sumU2 = 0.0f;
    double sumT = 0.0f;
    double sumT2 = 0.0f;

    /* simulation run */
    int i, count = 0;
    for(i = 0; i < total_steps; i++){
        if(!(i%10)) compute_table(particle,neighbour);
        integrate(particle,neighbour);
        if((i*dt<10)&&(i%10==0))
            reset_mom(particle, (ENERGY-U)/(H-U) );
        if((i*dt>10)&&(i%100==0)){
            reset_mom(particle, (ENERGY-U)/(H-U) );
            sumU += U;
            sumU2 += U*U;
            sumT += T;
            sumT2 += T*T;
            count++;
        }
        printf("%e %e %e %e %e\n", i*dt, H/N, U/N, K/N, T );
    }

    printf("# <U/N>=%e\tsqrt[<(U/N-<U/N>)²>]=%e\n", (sumU/count)/N, sqrt(sumU2/count-(sumU/count)*(sumU/count))/N );
    printf("# <T>=%e\tsqrt[<(T-<T>)²>]=%e\n", (sumT/count), sqrt(sumT2/count-(sumT/count)*(sumT/count)) );

    /* exit */
    free(particle);
    destroy_table(neighbour);
    return 0;
}
