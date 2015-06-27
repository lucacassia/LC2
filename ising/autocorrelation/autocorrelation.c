#include "ising.h"

void get_autocorrelation(FILE *f){

    raw storage = load_data(f,0);

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

    char filename[50];
    sprintf(filename, "data/%d_%f_%s_autocorrelation_time.dat", storage.l, storage.b, storage.algorithm );
    FILE *output = fopen(filename,"a");

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
        fprintf(output, "%f\t%d\t%f\n", storage.b, k_max, autocorrelation_time);
    }
    printf(" DONE!\n");
    printf("Written to: %s\n", filename);
    raw_close(&storage);
    fclose(output);
}

int main(){
/*
    step = 10;
    get_autocorrelation(MH,0.43);
    step = 1;
    get_autocorrelation(SW,0.43);
*/
    char filename[50];
    sprintf(filename, "data/32_0.430000_MH_100000.bin");
    printf("\nReading from: %s\n", filename);
    FILE *f = fopen(filename, "rb");
    get_autocorrelation(f);
    fclose(f);

/*
    step = 10;

    double x;
    for(x=-0.1;x<=0.1;x+=0.004)
        get_autocorrelation(MH,(x+1)*0.4406868);

    step = 1;

    for(x=-0.1;x<=0.1;x+=0.004)
        get_autocorrelation(SW,(x+1)*0.4406868);
*/
    return 0;
}
