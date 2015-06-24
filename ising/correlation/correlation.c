#include"ising.h"

void get_correlation(void (*algorithm)(), int bin_number, double beta_value){
    int i, j, t, dist, bin_size = get_bin_size(algorithm);
    char filename[50];
    sprintf(filename, "data/%s_correlation_%f_%d.dat", get_algorithm_string(algorithm), beta_value, bin_number);

    init(beta_value);
    printf("\nExecuting %s @ β = %f\n\n", get_algorithm_string(algorithm), beta_value);
    printf("Thermalizing................"); fflush(stdout); thermalize(algorithm); printf("DONE!\n");

    double *Sx, *Sy;
    double **correlation = (double**)malloc((size/2)*sizeof(double*));
    for(dist = 0; dist < size / 2; dist++) correlation[dist] = (double*)malloc(bin_number * sizeof(double));

    printf("Gathering Binned Data......."); fflush(stdout);
    for(t = 0; t < bin_number * bin_size; t++){
        algorithm();
        Sx = (double*)malloc(size * sizeof(double));
        Sy = (double*)malloc(size * sizeof(double));
        for(i = 0; i < size; i++){ Sx[i] = Sy[i] = 0.0f; }
        for(i = 0; i < size; i++) for(j = 0; j < size; j++){
            Sx[j] += ising[i][j].s / size;
            Sy[i] += ising[i][j].s / size;
        }
        for(dist = 0; dist < size / 2; dist++) for(i = 0; i < size; i++){
            correlation[dist][t / bin_size] += Sx[i] * Sx[(i+dist)%size];
            correlation[dist][t / bin_size] += Sx[i] * Sx[(size+i-dist)%size];
            correlation[dist][t / bin_size] += Sy[i] * Sy[(i+dist)%size];
            correlation[dist][t / bin_size] += Sy[i] * Sy[(size+i-dist)%size];
            correlation[dist][t / bin_size] /= 4 * size * bin_size;
        }
        free(Sx);
        free(Sy);
    }printf("DONE!\t%d Samples x %d Bin Gathered\n\n", bin_size, bin_number);

    FILE *f = fopen(filename,"w");
    double mean, variance;
    for(dist = 0; dist < size / 2; dist++){
        variance = mean = 0.0f;
        for(t = 0; t < bin_number; t++){
            mean += correlation[dist][t];
            variance += correlation[dist][t] * correlation[dist][t];
        }
        free(correlation[dist]);
        mean /= bin_number;
        variance = variance / bin_number - mean * mean;
        fprintf(f,"%d\t%f\t%f\t\n", dist, mean, variance);
    }
    free(correlation);
    fclose(f);
}

int main(){
    size = 128;
    get_correlation(MH,50,0.3);
    return 0;
}
