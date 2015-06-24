#include "ising.h"

void get_variance_bin(void (*algorithm)(), double beta_value, int step){

    char filename[50];
    sprintf(filename,"data/%s_variance_%f.dat", get_algorithm_string(algorithm), beta_value);

    FILE *f = fopen(filename,"w");

    int t, k;
    int storage_size = 1000000;

    double *storage = get_data(algorithm, beta_value, storage_size, get_energy);
    double old_mean = 0;
    for(t = 0; t < storage_size; t++)
        old_mean += storage[t];
    old_mean /= storage_size;
    double old_variance = 0;
    for(t = 0; t < storage_size; t++)
        old_variance += storage[t] * storage[t];
    old_variance = old_variance / storage_size - old_mean * old_mean;
    printf("μ  = %f\nσ² = %f\n",old_mean,old_variance);

    printf("Binning.............."); fflush(stdout);
    double *binned_data;

    for(k = 1; k < 100 * step; k += step){
        binned_data = bin_data(storage, storage_size, k);
        double mean = 0;
        for(t = 0; t < storage_size/k; t++)
            mean += binned_data[t];
        mean /= storage_size/k;
        double variance = 0;
        for(t = 0; t < storage_size/k; t++)
            variance += binned_data[t] * binned_data[t];
        variance = variance / (storage_size/k) - mean * mean;
        fprintf(f, "%d\t%f\n", k, k * variance / old_variance);
        free(binned_data);
    }
    printf("DONE!\n\nWritten to %s\n", filename);

    free(storage);
    fclose(f);
}

void plot_bined_data(void (*algorithm)(int), double beta_value, int bin_number, double (*func)() ){

    char filename[50];
    int t;

    if(func == get_energy)        { sprintf(filename,"data/energy_bin_%d_%f_%s.dat",bin_number,beta_value,get_algorithm_string(algorithm)); }
    if(func == get_magnetization) { sprintf(filename,"data/magnetization_bin_%d_%f_%s.dat",bin_number,beta_value,get_algorithm_string(algorithm)); }

    double *binned_data = get_binned_data(algorithm, beta_value, bin_number, func);
    FILE *f = fopen(filename,"w");
    for(t = 0; t < bin_number; t++){
        fprintf(f,"%f\n",binned_data[t]);
    }
    fclose(f);
    free(binned_data);

    printf("Written to: %s\n",filename);
}


int main(){

    plot_bined_data(MH,0.30,1000,get_magnetization);
    plot_bined_data(MH,0.43,1000,get_magnetization);

    plot_bined_data(SW,0.30,1000,get_magnetization_nofabs);
    plot_bined_data(SW,0.43,1000,get_magnetization_nofabs);

    void (*algorithm)() = NULL;

    if(algorithm == SW){
        get_variance_bin(algorithm,0.35,1);
        get_variance_bin(algorithm,0.40,1);
        get_variance_bin(algorithm,0.43,1);
        get_variance_bin(algorithm,0.44,1);
        get_variance_bin(algorithm,0.45,1);
        get_variance_bin(algorithm,0.50,1);
    }

    if(algorithm == MH){
        get_variance_bin(algorithm,0.35,10);
        get_variance_bin(algorithm,0.40,16);
        get_variance_bin(algorithm,0.43,50);
        get_variance_bin(algorithm,0.44,50);
        get_variance_bin(algorithm,0.45,50);
        get_variance_bin(algorithm,0.50,10);
    }

    return 0;
}
