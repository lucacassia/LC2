#include"ising.h"

void plot_observable_bin(void (*algorithm)(int), double beta_value, int bin_number, double (*func)() ){

    char filename[50];
    char *algorithm_string;
    int t;

    if(algorithm == MH){ algorithm_string = "MH"; }
    if(algorithm == SW){ algorithm_string = "SW"; }
    if(func == get_energy)        { sprintf(filename,"data/energy_bin_%d_%f_%s.dat",bin_number,beta_value,algorithm_string); }
    if(func == get_magnetization) { sprintf(filename,"data/magnetization_bin_%d_%f_%s.dat",bin_number,beta_value,algorithm_string); }

    double *binned_data = get_binned_data(algorithm, beta_value, bin_number, func);
    FILE *f = fopen(filename,"w");
    for(t = 0; t < bin_number; t++){
        fprintf(f,"%f\n",binned_data[t]);
    }
    fclose(f);
    free(binned_data);

    printf("Written to: %s\n",filename);
}

void plot_observable(void (*algorithm)(int), int bin_number, double (*func)(), int n){

    char filename[50];
    char *algorithm_string;
    int t;
    double beta_value, mean, std;
    double *binned_data;

    if(algorithm == MH){ algorithm_string = "MH"; }
    if(algorithm == SW){ algorithm_string = "SW"; }
    if(func == get_energy)        { sprintf(filename,"data/energy_plot_%d_%s.dat",bin_number,algorithm_string); }
    if(func == get_magnetization) { sprintf(filename,"data/magnetization_plot_%d_%s.dat",bin_number,algorithm_string); }

    FILE *f = fopen(filename,"w");
    for(beta_value = 0; beta_value <= 1; beta_value += 1.0f / n){

        binned_data = get_binned_data(algorithm, beta_value, bin_number, func);

        mean = std = 0.0f;
        for(t = 0; t < bin_number; t++)
            mean += binned_data[t];
        mean /= bin_number;
        for(t = 0; t < bin_number; t++)
            std += binned_data[t] * binned_data[t];
        std = sqrt( std / bin_number - mean * mean );
        fprintf(f, "%f\t%f\t%f\n", beta_value, mean, std);

        free(binned_data);
    }
    fclose(f);
    printf("Written to: %s\n",filename);
}

int main(){
/*
    plot_observable_bin(0,0.80,1000,get_magnetization);
    plot_observable_bin(0,0.30,1000,get_magnetization);
    plot_observable_bin(0,0.42,1000,get_magnetization);
    plot_observable_bin(0,0.43,1000,get_magnetization);
    plot_observable_bin(0,0.44,1000,get_magnetization);
    plot_observable_bin(0,0.46,1000,get_magnetization);
*/
    plot_observable(MH,100,get_energy,100);
    return 0;
}
