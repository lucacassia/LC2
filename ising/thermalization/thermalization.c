#include "ising.h"

int thermalization(void (*algorithm)(), double beta_value, double (*func)()){
    char filename[50];
    sprintf(filename,"data/%s_thermalization_%f.dat", get_algorithm_string(algorithm), beta_value);
    FILE *f = fopen(filename,"w");
    init(beta_value);
    printf("\nExecuting %s @ β = %f\n\n", get_algorithm_string(algorithm), beta_value);
    int t;
    for(t = 0; t < 2000; t++){
        algorithm();
        fprintf(f,"%u\t%e\t%e\n", t, func()/(size*size), beta_value);
    }
    fclose(f);
    return 0;
}

int main(){

    thermalization(MH,0.50,get_magnetization_nofabs);
    thermalization(MH,0.30,get_magnetization_nofabs);
    thermalization(MH,0.40,get_magnetization_nofabs);
    thermalization(MH,0.45,get_magnetization_nofabs);
    thermalization(MH,0.60,get_magnetization_nofabs);
    thermalization(MH,0.80,get_magnetization_nofabs);

    thermalization(SW,0.50,get_magnetization);
    thermalization(SW,0.30,get_magnetization);
    thermalization(SW,0.40,get_magnetization);
    thermalization(SW,0.45,get_magnetization);
    thermalization(SW,0.60,get_magnetization);
    thermalization(SW,0.80,get_magnetization);


    int t;
    init(0.3);
    thermalize(MH);
    FILE *f = fopen("data/MH_magnetization_0.300000.dat","w");
    for(t = 0; t < 1000; t++){
        MH();
        fprintf(f,"%u\t%e\t%e\n", t, get_magnetization_nofabs()/(size*size), beta);
    }
    fclose(f);

    f = fopen("data/SW_magnetization_0.300000.dat","w");
    for(t = 0; t < 1000; t++){
        SW();
        fprintf(f,"%u\t%e\t%e\n", t, get_magnetization()/(size*size), beta);
    }
    fclose(f);

    clear();
    return 0;
}
