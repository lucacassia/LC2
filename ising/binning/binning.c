#include "ising.h"

void get_variance_bin(int algorithm_id, double beta_value){

    char filename[50];
    sprintf(filename,"data/variance_%d_%f.dat", algorithm_id, beta_value);

    FILE *f = fopen(filename,"w");

    int storage_size, t, k, step;

    if(!algorithm_id){
        storage_size = 1000000;
        step = 100;
    }else{
        storage_size = 50000;
        step = 2;
    }

    double *storage = get_data(algorithm_id, beta_value, storage_size);
    double old_mean = 0;
    for(t = 0; t < storage_size; t++)
        old_mean += storage[t];
    old_mean /= storage_size;
    double old_variance = 0;
    for(t = 0; t < storage_size; t++)
        old_variance += storage[t] * storage[t];
    old_variance = old_variance / storage_size - old_mean * old_mean;
    printf("μ  = %f\nσ² = %f\n",old_mean,old_variance);

    printf("Binning..."); fflush(stdout);
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
    printf("...........DONE!\n");

    free(storage);
    fclose(f);
}

int main(){
    get_variance_bin(1,0.35);
    get_variance_bin(1,0.40);
    get_variance_bin(1,0.43);
    get_variance_bin(1,0.44);
    get_variance_bin(1,0.45);
    get_variance_bin(1,0.50);
    return 0;
}
