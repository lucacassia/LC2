#include "ising.h"

int termalize(FILE* f, double beta_value, unsigned int algorithm_id, unsigned int markov_time_max){
    int i;
    algorithm = algorithm_id;
    init(); beta = beta_value;
    if (algorithm == 0) printf("\nMetropolis-Hasting Algorithm\t");
    if (algorithm == 1) printf("\nSwendsen-Wang Algorithm\t");
    printf("beta = %f\n",beta);
    for(i = 0; i < markov_time_max; i++){
        run();
        fprintf(f,"%u\t%e\t%e\n", markov_time, get_energy()/(width*height), beta);
    }
    return 0;
}

int main(){
    FILE *f1 = fopen("data/termalization_MH_critical.dat","w");
    termalize(f1,0.44,0,500);    fclose(f1);

    FILE *f2 = fopen("data/termalization_MH.dat","w");
    for(beta = 0.3; beta <= 0.6; beta += 0.1)   termalize(f2,beta,0,100);    fclose(f2);

    FILE *f3 = fopen("data/termalization_SW_critical.dat","w");
    termalize(f3,0.44,1,500);    fclose(f3);

    FILE *f4 = fopen("data/termalization_SW.dat","w");
    for(beta = 0.3; beta <= 0.6; beta += 0.1)   termalize(f4,beta,1,100);   fclose(f4);

    return 0;
}
