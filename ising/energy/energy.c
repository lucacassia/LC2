#include"ising.h"

void get_energy_plot(int algorithm_id, double beta_value, FILE *f){
    int bin_number, bin_size;
    if(!algorithm_id){
        bin_size = 200000;
        bin_number = 10;
    }else{
        bin_size = 400;
        bin_number = 10;
    }
    double *storage = get_binned_data(algorithm_id, beta_value, bin_size, bin_number);
    double mean = 0;
    double variance = 0;
    int t;
    for(t = 0; t < bin_number; t++)
        mean += storage[t];
    mean /= bin_number;
    for(t = 0; t < bin_number; t++)
        variance += storage[t] * storage[t];
    variance = variance / bin_number - mean * mean;
    fprintf(f, "%f\t%f\t%f", beta_value, mean, sqrt(variance) );
    free(storage);
    clear();
    
}

int main(){
    FILE *f = fopen("data/energy_MH","w");
    double b;
    for(b = 0.0f; b < 1; b += 0.1)
        get_energy_plot(0,b,f);
    fclose(f);
    return 0;
}
