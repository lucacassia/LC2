/*
 *  usage: ./pressure > output
 */

#define DIMENSION 3

#include"softcore.h"

int main(int argc, char *argv[])
{
    /* MD settings */
    N = 108;
    rho = 0.6;
    L = pow(N/rho, 1.0f/DIMENSION);
    double TEMP = 1.22;

    int total_steps = 11e4;

    /* allocate memory */
    obj *particle = (obj*)malloc(N*sizeof(obj));
    int **neighbour = NULL;
    neighbour = create_table(neighbour);

    init_pos(particle,N/2,0.0);
    init_pos(&particle[N/2],N-N/2,0.5);

    init_mom(particle);
    reset_mom(particle,TEMP/T);
    compute_table(particle,neighbour);
    get_acc(particle,neighbour);

    /* print header */
    printf("#N=%d rho=%f L=%f T=%f dt=%f\n", N, rho, L, T, dt);
    printf("#\tt\tH\tU\tK\tT\n");

    double sumU = 0.0f;
    double sumU2 = 0.0f;
    double sumT = 0.0f;
    double sumT2 = 0.0f;
    double sumP = 0.0f;
    double sumP2 = 0.0f;

    FILE *f = fopen("data/pressure.dat","w");
    /* simulation run */
    int i, count = 0;
    for(i = 0; i < total_steps; i++){
        if(!(i%10)) compute_table(particle,neighbour);
        integrate(particle,neighbour);
        if((i*dt<10)&&(i%10==0)) reset_mom(particle,TEMP/T);
        if((i*dt>10)&&(i%100==0)){
            sumU += U;
            sumU2 += U*U;
            sumT += T;
            sumT2 += T*T;

            /* pressure */
            work = work/(DIMENSION*100*N*T)-1;
            sumP += work;
            sumP2 += work*work;
            fprintf(f,"%e\t%e\n",i*dt,work);
            work = 0.0f;

            count++;
        }
        
        printf("%e %e %e %e %e\n", i*dt, H/N, U/N, K/N, T );
    }
    fclose(f);
    printf("# <U/N>=%e\tsqrt[<(U/N-<U/N>)²>]=%e\n", (sumU/count)/N, sqrt(sumU2/count-(sumU/count)*(sumU/count))/N );
    printf("# <T>=%e\tsqrt[<(T-<T>)²>]=%e\n", (sumT/count), sqrt(sumT2/count-(sumT/count)*(sumT/count)) );
    printf("# <P>=%e\tsqrt[<(P-<P>)²>]=%e\n", (sumP/count), sqrt(sumP2/count-(sumP/count)*(sumP/count)) );

    /* exit */
    free(particle);
    destroy_table(neighbour);
    return 0;
}
