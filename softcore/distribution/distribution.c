#define DIMENSION 3

#include"softcore.h"

int main(int argc, char *argv[])
{
    /* MD settings */

    if(argc == 3){
        N = atoi(argv[1]);
        rho = atof(argv[2]);
    }
    else return 1;

    L = pow(N/rho, 1.0f/DIMENSION);
    double TEMPERATURE = 1.0f;

    /* allocate memory */
    obj *particle = (obj*)malloc(N*sizeof(obj));
    int **neighbour = NULL;
    neighbour = create_table(neighbour);

    init_pos(particle,N/2,0.0);
    init_pos(&particle[N/2],N-N/2,0.5);

    init_mom(particle);
    reset_mom(particle,TEMPERATURE/T);
    compute_table(particle,neighbour);
    get_acc(particle,neighbour);

    /* print header */
    printf("#N=%d rho=%f L=%f T=%f dt=%f\n", N, rho, L, T, dt);

    /* thermalization */
    int i,j;
    for(i = 0; i < 5e3; i++){
        if(i%10==0) compute_table(particle,neighbour);
        integrate(particle,neighbour);
        if(i%10==0) reset_mom(particle,TEMPERATURE/T);
    }

    /* simulation run */
    FILE *f = fopen("data/distribution.dat","w");
    for(i = 0; i < 1e6; i++){
        if(i%10==0) compute_table(particle,neighbour);
        integrate(particle,neighbour);
        if(!(i%100)) for(j=0;j<N;j++) fprintf(f,"%e\t%e\t%e\t%e\n",modulus(particle[j].mom),particle[j].mom[0],particle[j].mom[1],particle[j].mom[2]);
    }
    fclose(f);

    /* exit */
    free(particle);
    destroy_table(neighbour);
    return 0;
}
