#include"ising.h"

void plot_observable_bin(int algorithm_id, double beta_value, int bin_number, double (*func)() ){

    char filename[50];
    int t, bin_size;

    if(!algorithm_id){
        bin_size = 200000;
        sprintf(filename,"data/energy_bin_%d_MH.dat",bin_number);
    }else{
        bin_size = 400;
        sprintf(filename,"data/energy_bin_%d_SW.dat",bin_number);
    }

    double *binned_data = get_binned_data(algorithm_id, beta_value, bin_size, bin_number, func);
    FILE *f = fopen(filename,"w");
    for(t = 0; t < bin_number; t++){
        fprintf(f,"%f\n",binned_data[t]);
    }
    fclose(f);
    free(binned_data);
}

void plot_observable(int algorithm_id, double beta_value, int bin_number, double (*func)(), FILE *f){

    int t, bin_size;

    if(!algorithm_id){ bin_size = 200000; }else{ bin_size = 400; }

    double *binned_data = get_binned_data(algorithm_id, beta_value, bin_size, bin_number, func);

    double mean = 0.0f;
    double std = 0.0f;

    for(t = 0; t < bin_number; t++)
        mean += binned_data[t];
    mean /= bin_number;
    for(t = 0; t < bin_number; t++)
        std += binned_data[t] * binned_data[t];
    std = sqrt( std / bin_number - mean * mean );
    fprintf(f, "%f\t%f\t%f\n", beta_value, mean, std);

    free(binned_data);
}

int main(){

    FILE *f = fopen("data/energy_plot_SW.dat","w");
    double b;
    for(b = 0.0f; b <= 1; b += 0.05)
        plot_observable(0,b,100,get_energy,f);
    fclose(f);

    return 0;
}
