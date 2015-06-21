#include "ising.h"

void get_variance_bin(void (*algorithm)(int), double beta_value){

    char *algorithm_string = NULL;
    if( algorithm == MH ){ algorithm_string = "MH"; }
    if( algorithm == SW ){ algorithm_string = "SW"; }
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); }
    char filename[50];
    sprintf(filename,"data/variance_%s_%f.dat", algorithm_string, beta_value);

    FILE *f = fopen(filename,"w");

    int storage_size, t, k, step;

    if(algorithm == MH){
        storage_size = 1000000;
        step = 100;
    }
    if(algorithm == SW){
        storage_size = 50000;
        step = 2;
    }

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

    for(k = 1; k < 100*step; k += step){
        binned_data = bin_data(storage, storage_size, k);
        double mean = 0;
        for(t = 0; t < storage_size/k; t++)
            mean += binned_data[t];
        mean /= storage_size/k;
        double variance = 0;
        for(t = 0; t < storage_size/k; t++)
            variance += binned_data[t] * binned_data[t];
        variance = variance / (storage_size/k) - mean * mean;
        fprintf(f,"%d\t%f\n",k,k*variance/old_variance);
        free(binned_data);
    }
    printf("DONE!\n\nWritten to %s\n",filename);

    free(storage);
    fclose(f);
}

int main(){
    get_variance_bin(MH,0.35);
    return 0;
}
