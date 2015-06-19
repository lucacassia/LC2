#include"ising.h"

void get_energy_plot(int algorithm_id, double beta_value, int bin_number){

    char filename[50];
    int bin_size;
    if(!algorithm_id){
        bin_size = 200000;
        sprintf(filename,"data/energy_bin_%d_MH.dat",bin_number);

    }else{
        bin_size = 400;
        sprintf(filename,"data/energy_bin_%d_SW.dat",bin_number);
    }

    FILE *f = fopen(filename,"w");

    double *binned_data = get_binned_data(algorithm_id, beta_value, bin_size, bin_number);

    double mean = 0.0f;
    double variance = 0.0f;

    int t;

    mean = variance = 0.0f;
    for(t = 0; t < bin_number; t++){
        fprintf(f,"%f\n",binned_data[t]);
        mean += binned_data[t];
    }fclose(f);

    mean /= bin_number;
    printf("μ  = %f\t(binned)\n", mean );
    for(t = 0; t < bin_number; t++)
        variance += binned_data[t] * binned_data[t];
    variance = variance / bin_number - mean * mean;
    printf("σ² = %f\t(binned)\n\n", variance );

    free(binned_data);
}

int main(){
    get_energy_plot(1,0.3,1000);
    return 0;
}
