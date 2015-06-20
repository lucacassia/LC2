#include"ising.h"

void plot_observable_bin(int algorithm_id, double beta_value, int bin_number, double (*func)() ){

    char filename[50];
    int t, bin_size;

    if(!algorithm_id){
        bin_size = 200000;
        if(func == get_energy)          sprintf(filename,"data/energy_bin_%d_%f_MH.dat",bin_number,beta_value);
        if(func == get_magnetization)   sprintf(filename,"data/magnetization_bin_%d_%f_MH.dat",bin_number,beta_value);
    }else{
        bin_size = 400;
        if(func == get_energy)          sprintf(filename,"data/energy_bin_%d_%f_SW.dat",bin_number,beta_value);
        if(func == get_magnetization)   sprintf(filename,"data/magnetization_bin_%d_%f_SW.dat",bin_number,beta_value);
    }

    double *binned_data = get_binned_data(algorithm_id, beta_value, bin_size, bin_number, func);
    FILE *f = fopen(filename,"w");
    for(t = 0; t < bin_number; t++){
        fprintf(f,"%f\n",binned_data[t]);
    }
    fclose(f);
    free(binned_data);

    printf("Written to: %s\n",filename);
}

void plot_observable(int algorithm_id, int bin_number, double (*func)(), int n){

    char filename[50];
    int t, bin_size;
    double beta_value, mean, std;
    double *binned_data;
    FILE *f;

    if(!algorithm_id){
        bin_size = 200000;
        if(func == get_energy)          sprintf(filename,"data/energy_plot_%d_MH.dat",bin_number);
        if(func == get_magnetization)   sprintf(filename,"data/magnetization_plot_%d_MH.dat",bin_number);
    }else{
        bin_size = 400;
        if(func == get_energy)          sprintf(filename,"data/energy_plot_%d_SW.dat",bin_number);
        if(func == get_magnetization)   sprintf(filename,"data/magnetization_plot_%d_SW.dat",bin_number);
    }

    f = fopen(filename,"w");
    for(beta_value = 0; beta_value <= 1; beta_value += 1.0f / n){

        binned_data = get_binned_data(algorithm_id, beta_value, bin_size, bin_number, func);

        mean = std = 0.0f;
        for(t = 0; t < bin_number; t++)
            mean += binned_data[t];
        mean /= bin_number;
        for(t = 0; t < bin_number; t++)
            std += binned_data[t] * binned_data[t];
        std = sqrt( std / bin_number - mean * mean );
        free(binned_data);
        fprintf(f, "%f\t%f\t%f\n", beta_value, mean, std);
    }
    fclose(f);
    printf("Written to: %s\n",filename);
}

int main(){
/*    plot_observable_bin(0,0.8,100,get_magnetization);*/
    plot_observable(0,50,get_magnetization,40);
    return 0;
}
