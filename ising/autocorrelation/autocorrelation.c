#include "ising.h"

int storage_size, step1, step2, k_max_star;

void get_autocorrelation(int algorithm_id, double beta_value){

    int t, k, k_max;

    double *storage = get_data(algorithm_id, beta_value, storage_size, get_energy);

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
    printf("μ  = %f\nσ² = %f\n",mean,variance);
    printf("\nComputing Autocorrelations..."); fflush(stdout);

    char filename1[50];    sprintf(filename1,"data/autocorrelation_%d_%f.dat",algorithm_id,beta_value);
    char filename2[50];    sprintf(filename2,"data/autocorrelation_time_%d_%f.dat",algorithm_id,beta_value);

    FILE *f1 = fopen(filename1,"w");
    FILE *f2 = fopen(filename2,"w");

    double autocorrelation, autocorrelation_time;
    for(k_max = 0; k_max < 100 * step1; k_max += step1){
        autocorrelation_time = 0.5;
        for(k = 0; k < k_max; k++){
            autocorrelation = 0.0f;
            for(t = 0; t < storage_size - k; t++)
                autocorrelation += storage[t] * storage[t+k];
            autocorrelation /= variance * (storage_size-k);
            autocorrelation_time += autocorrelation;
/*            if(k_max == k_max_star && k%step2 == 0 )   fprintf(f1, "%d\t%f\n", k, autocorrelation);*/
        }
        fprintf(f2,"%d\t%f\n",k_max,autocorrelation_time);
    }

    free(storage);

    fclose(f1);
    fclose(f2);

    printf("DONE!\n");
}

int main(){

    storage_size = 100000;
    step1 = 200;
    step2 = 100;
    k_max_star = 8000;

    double b;
    for(b=0.35;b<0.56;b+=0.01)
        get_autocorrelation(0,b);

    storage_size = 50000;
    step1 = 2;
    step2 = 2;
    k_max_star = 50;

    for(b=0.35;b<0.56;b+=0.01)
        get_autocorrelation(1,b);

    return 0;
}
