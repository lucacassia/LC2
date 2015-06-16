#include "ising.h"

double get_moment(int n, double* storage, int storage_size){
    double tmp=0; int i; for(i=0;i<storage_size;i++) tmp+=pow(storage[i],n);
    return tmp/storage_size;
}

int main(){

    beta = 0.3;
    unsigned int algorithm_id = 0;

    FILE *f1 = fopen("data/energy.dat","w");
    FILE *f2 = fopen("data/autocorrelation.dat","w");
    FILE *f3 = fopen("data/autocorrelation_time.dat","w");

    termalize(algorithm_id, 500);

    unsigned int storage_size = 100000;
    double* storage = (double*)malloc(storage_size * sizeof(double));
    int k,k_max,t;
    for(t = 0; t < storage_size; t++){
        single_MH( (t/width)%height, t%width);
        storage[t] = get_energy() / (height * width);
        fprintf(f1, "%f\n", storage[t]);
    }

    double variance, mean;
    mean = get_moment(1,storage,storage_size);
    variance = get_moment(2,storage,storage_size)-mean*mean;
    printf("Mean = %f\nVariance = %f\n",mean,variance);

    for(t = 0; t < storage_size; t++){
        storage[t] -= mean;
    }

    double autocorrelation, autocorrelation_time;
    for(k_max = 0; k_max < 35000; k_max+=500){
        autocorrelation_time = 0.5;
        for(k = 0; k < k_max; k++){
            autocorrelation = 0.0f;
            for(t = 0; t < storage_size - k; t++)
                autocorrelation += storage[t] * storage[t+k];
            autocorrelation /= variance * (storage_size-k);
            autocorrelation_time += autocorrelation;
            if(k_max == 10000)   fprintf(f2, "%d\t%f\n", k, autocorrelation);
        }
        fprintf(f3,"%d\t%f\n",k_max,autocorrelation_time);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}
