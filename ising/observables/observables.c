#include"ising.h"

void plot_observables(void (*algorithm)(), int bin_number, double start, double end, int n_points){

    FILE *f[2];
    char filename[2][50];

    sprintf(filename[0],"data/%s_plot_e_%d.dat",get_algorithm_string(algorithm),bin_number);
    sprintf(filename[1],"data/%s_plot_m_%d.dat",get_algorithm_string(algorithm),bin_number);

    f[0] = fopen(filename[0],"a");
    f[1] = fopen(filename[1],"a");

    double beta_value, mean[2], std[2];
    double **binned_data;

    int t;
    for(beta_value = start; beta_value <= end; beta_value += (end - start) / n_points){

        binned_data = get_binned_data(algorithm, beta_value, bin_number);

        mean[0] = mean[1] = std[0] = std[1] = 0.0f;
        for(t = 0; t < bin_number; t++){
            mean[0] += binned_data[0][t];
            mean[1] += binned_data[1][t];
        }
        mean[0] /= bin_number;
        mean[1] /= bin_number;
        for(t = 0; t < bin_number; t++){
            std[0] += binned_data[0][t] * binned_data[0][t];
            std[1] += binned_data[1][t] * binned_data[1][t];
        }
        std[0] = sqrt( std[0] / bin_number - mean[0] * mean[0] );
        std[1] = sqrt( std[1] / bin_number - mean[1] * mean[1] );
        fprintf(f[0], "%f\t%f\t%f\n", beta_value, mean[0], std[0]);
        fprintf(f[1], "%f\t%f\t%f\n", beta_value, mean[1], std[1]);

        free(binned_data[0]);
        free(binned_data[1]);
        free(binned_data);
    }
    fclose(f[0]);
    fclose(f[1]);
    printf("Written to: %s\n",filename[0]);
    printf("            %s\n",filename[1]);
}

int main(){
    plot_observables(SW,100,0.3f,0.6f,50);
    return 0;
}
