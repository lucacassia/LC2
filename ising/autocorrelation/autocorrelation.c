#include "ising.h"

int storage_size, step;

void get_autocorrelation(void (*algorithm)(int), double beta_value){

    double *storage = get_data(algorithm, beta_value, storage_size, get_energy);

    double mean = 0;
    int t, k, k_max;
    for(t = 0; t < storage_size; t++)
        mean += storage[t];
    mean /= storage_size;
    double variance = 0;
    for(t = 0; t < storage_size; t++)
        variance += storage[t] * storage[t];
    variance = variance / storage_size - mean * mean;
    for(t = 0; t < storage_size; t++)
        storage[t] -= mean;
    printf("μ  = %f\nσ² = %f\n",mean,variance);
    printf("\nComputing Autocorrelations.."); fflush(stdout);

    char filename[50];
    sprintf(filename, "data/%s_autocorrelation_time_%f.dat", get_algorithm_string(algorithm), beta_value);
    FILE *f = fopen(filename,"w");

    double autocorrelation, autocorrelation_time;
    for(k_max = 0; k_max < 100 * step; k_max += step){
        autocorrelation_time = 0.5f;
        for(k = 0; k < k_max; k++){
            autocorrelation = 0.0f;
            for(t = 0; t < storage_size - k; t++)
                autocorrelation += storage[t] * storage[t+k];
            autocorrelation /= variance * (storage_size - k);
            autocorrelation_time += autocorrelation;
        }
        fprintf(f, "%f\t%d\t%f\n", beta_value, k_max, autocorrelation_time);
    }
    printf("DONE!\n");
    free(storage);
    fclose(f);

}

int main(){

    storage_size = 100000;
    step = 10;

    double b;
    for(b=-0.1;b<=0.1;b+=0.004)
        get_autocorrelation(MH,(b+1)*0.4406868);

    storage_size = 50000;
    step = 1;

    for(b=-0.1;b<0.1;b+=0.004)
        get_autocorrelation(SW,(b+1)*0.4406868);

    return 0;
}
