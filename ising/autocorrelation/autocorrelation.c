#include "ising.h"

void get_autocorrelation(char *input){

    FILE *f = fopen(input, "rb");
    raw storage = load_data(f,0,1000);
    fclose(f);

    int step = 1;
    if(!storage.id) step = 10;
    double mean = 0;
    int t, k, k_max;
    for(t = 0; t < storage.size; t++)
        mean += storage.data[t];
    mean /= storage.size;
    double variance = 0;
    for(t = 0; t < storage.size; t++)
        variance += storage.data[t] * storage.data[t];
    variance = variance / storage.size - mean * mean;
    for(t = 0; t < storage.size; t++)
        storage.data[t] -= mean;

    printf("μ  = %f\nσ² = %f\n",mean,variance);
    printf("Computing Autocorrelations..."); fflush(stdout);

    char output[50];
    sprintf(output, "data/%d_%f_%s_%d.acr", storage.l, storage.b, storage.algorithm, storage.size );
    f = fopen(output,"a");
    fprintf(f, "#\t%d\t%f\t%s\t%d\n", storage.l, storage.b, storage.algorithm, storage.size );

    double autocorrelation, autocorrelation_time;
    for(k_max = 0; k_max < 100 * step; k_max += step){
        autocorrelation_time = 0.5f;
        for(k = 0; k < k_max; k++){
            autocorrelation = 0.0f;
            for(t = 0; t < storage.size - k; t++)
                autocorrelation += storage.data[t] * storage.data[t+k];
            autocorrelation /= variance * (storage.size - k);
            autocorrelation_time += autocorrelation;
        }
        fprintf(f, "%d\t%f\n", k_max, autocorrelation_time);
    }
    printf(" DONE!\n");
    printf("Written to: %s\n", output);
    raw_close(&storage);
    fclose(f);
}

int main(){

    char filename[50];
    double x;
    for(x = -0.1; x <= 0.1; x += 0.004){
        sprintf(filename, "data/32_%f_MH_100000.bin",(x+1) * BETA_CRITICAL);
        printf("\nReading from: %s\n", filename);
        get_autocorrelation(filename);
        sprintf(filename, "data/32_%f_SW_100000.bin",(x+1) * BETA_CRITICAL);
        printf("\nReading from: %s\n", filename);
        get_autocorrelation(filename);
    }

    return 0;
}
