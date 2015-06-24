#include "ising.h"

int thermalization(void (*algorithm)(), double beta_value, double (*func)()){
    char filename[50];
    sprintf(filename,"data/%s_thermalization_%f.dat", get_algorithm_string(algorithm), beta_value);
    FILE *f = fopen(filename,"w");
    init(beta_value);
    printf("\nExecuting %s @ β = %f\n\n", get_algorithm_string(algorithm), beta_value);
    int t;
    for(t = 0; t < 500; t++){
        algorithm();
        fprintf(f,"%u\t%e\t%e\n", t, func()/(size*size), beta_value);
    }
    fclose(f);
    return 0;
}

int main(){

    thermalization(MH,0.50,get_energy);
    thermalization(MH,0.30,get_energy);
    thermalization(MH,0.40,get_energy);
    thermalization(MH,0.43,get_energy);
    thermalization(MH,0.60,get_energy);
    thermalization(MH,0.80,get_energy);

    thermalization(SW,0.50,get_energy);
    thermalization(SW,0.30,get_energy);
    thermalization(SW,0.40,get_energy);
    thermalization(SW,0.43,get_energy);
    thermalization(SW,0.60,get_energy);
    thermalization(SW,0.80,get_energy);


    int t;
    init(0.43);
    thermalize(MH);

    FILE *f;
    char filename[50];

    sprintf(filename, "data/MH_energy_%f.dat", beta);
    f = fopen(filename,"w");
    for(t = 0; t < 500; t++){
        MH();
        fprintf(f,"%u\t%e\t%e\n", t, get_energy()/(size*size), beta);
    }
    fclose(f);

    sprintf(filename, "data/SW_energy_%f.dat", beta);
    f = fopen(filename,"w");
    for(t = 0; t < 500; t++){
        SW();
        fprintf(f,"%u\t%e\t%e\n", t, get_energy()/(size*size), beta);
    }
    fclose(f);

    clear();
    return 0;
}
