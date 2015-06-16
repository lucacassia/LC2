#include "ising.h"

int fprint_termalization(FILE* f, double beta_value, unsigned int algorithm_id, unsigned int markov_time_max){
    init(); beta = beta_value;
    if (algorithm_id == 0) printf("\nMetropolis-Hasting Algorithm\t");
    if (algorithm_id == 1) printf("\nSwendsen-Wang Algorithm\t");
    printf("beta = %f\n",beta);
    int t; for(t = 0; t < markov_time_max; t++){
        run(algorithm_id);
        if (algorithm_id == 0) fprintf(f,"%u\t%e\t%e\n", markov_time*width*height, get_energy()/(width*height), beta);
        if (algorithm_id == 1) fprintf(f,"%u\t%e\t%e\n", markov_time, get_energy()/(width*height), beta);
    }
    return 0;
}

int main(){
    FILE *f1 = fopen("data/termalization_MH_critical.dat","w");
    fprint_termalization(f1,0.45,0,300);    fclose(f1);

    FILE *f2 = fopen("data/termalization_MH.dat","w");
    for(beta = 0.3; beta <= 0.6; beta += 0.1)   fprint_termalization(f2,beta,0,300);    fclose(f2);

    FILE *f3 = fopen("data/termalization_SW_critical.dat","w");
    fprint_termalization(f3,0.45,1,300);    fclose(f3);

    FILE *f4 = fopen("data/termalization_SW.dat","w");
    for(beta = 0.3; beta <= 0.6; beta += 0.1)   fprint_termalization(f4,beta,1,300);   fclose(f4);

    return 0;
}
