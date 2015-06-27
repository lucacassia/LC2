#include "ising.h"

void get_variance_bin(char *input, int step){

    FILE *f = fopen(input, "rb");
    raw storage = load_data(f,0,1000);
    fclose(f);

    char output[50];
    sprintf(output, "data/%d_%f_%s_%d.var", storage.l, storage.b, storage.algorithm, storage.size );
    f = fopen(output,"w");
    fprintf(f, "#\t%d\t%f\t%s\t%d\n", storage.l, storage.b, storage.algorithm, storage.size );

    int t, k;

    double old_mean = 0;
    for(t = 0; t < storage.size; t++)
        old_mean += storage.data[t];
    old_mean /= storage.size;
    double old_variance = 0;
    for(t = 0; t < storage.size; t++)
        old_variance += storage.data[t] * storage.data[t];
    old_variance = old_variance / storage.size - old_mean * old_mean;
    printf("μ  = %f\nσ² = %f\n", old_mean, old_variance);

    printf("Binning.............."); fflush(stdout);
    double *binned_data;

    for(k = 1; k < 100 * step; k += step){
        binned_data = jackknife_data(storage.data, storage.size, k);
        double mean = 0;
        for(t = 0; t < storage.size/k; t++)
            mean += binned_data[t];
        mean /= storage.size/k;
        double variance = 0;
        for(t = 0; t < storage.size/k; t++)
            variance += binned_data[t] * binned_data[t];
        variance = variance / (storage.size/k) - mean * mean;
        fprintf(f, "%d\t%f\n", k, k * variance / old_variance);
        free(binned_data);
    }
    printf(" DONE!\n");
    printf("Written to: %s\n", output);
    raw_close(&storage);
    fclose(f);
}

int main(){

    get_variance_bin("data/32_0.350000_MH_1000000.bin",1);
    get_variance_bin("data/32_0.400000_MH_1000000.bin",16);
    get_variance_bin("data/32_0.430000_MH_1000000.bin",50);
    get_variance_bin("data/32_0.440687_MH_1000000.bin",50);
    get_variance_bin("data/32_0.450000_MH_1000000.bin",50);
    get_variance_bin("data/32_0.500000_MH_1000000.bin",5);

    get_variance_bin("data/32_0.350000_SW_1000000.bin",1);
    get_variance_bin("data/32_0.400000_SW_1000000.bin",1);
    get_variance_bin("data/32_0.430000_SW_1000000.bin",1);
    get_variance_bin("data/32_0.440687_SW_1000000.bin",1);
    get_variance_bin("data/32_0.450000_SW_1000000.bin",1);
    get_variance_bin("data/32_0.500000_SW_1000000.bin",1);

    return 0;
}
