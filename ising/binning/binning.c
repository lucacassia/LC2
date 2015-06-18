#include "ising.h"

void get_variance_bin(int algorithm_id, double beta_value){

    char filename[50];
    sprintf(filename,"data/variance_%d_%f.dat", algorithm_id, beta_value);

    FILE *f = fopen(filename,"w");

    int storage_size, t, k, k_max;

    if(!algorithm_id){
        storage_size = 100000;
    }else{
        storage_size = 50000;
    }

    double *storage = get_data(algorithm_id, beta_value, storage_size);

    double mean = 0;
    for(t = 0; t < storage_size; t++)
        mean += storage[t];
    mean /= storage_size;
    double variance = 0;
    for(t = 0; t < storage_size; t++)
        variance += storage[t] * storage[t];
    variance = variance / storage_size - mean * mean;
    for(t = 0; t < storage_size; t++)
        storage[t] -= mean;

    printf("Mean = %f\nVariance = %f\n",mean,variance);
    printf("\nComputing Autocorrelations..."); fflush(stdout);

    double autocorrelation, autocorrelation_time;
    for(k_max = 0; k_max < 50 * step; k_max += step){
        autocorrelation_time = 0.5;
        for(k = 0; k < k_max; k++){
            autocorrelation = 0.0f;
            for(t = 0; t < storage_size - k; t++)
                autocorrelation += storage[t] * storage[t+k];
            autocorrelation /= variance * (storage_size-k);
            autocorrelation_time += autocorrelation;
            if(k_max==k_max_star)   fprintf(f1, "%d\t%f\n", k, autocorrelation);
        }
        fprintf(f2,"%d\t%f\n",k_max,autocorrelation_time);
    }

    free(storage);
    fclose(f1);
    fclose(f2);
    clear();

    printf("DONE!\n");
}

int main(){
    get_autocorrelation(1,0.3);
    return 0;
}
