#include"ising.h"

void plot_correlation(int algorithm_id, int bin_number, int n){

    char filename[50];
    int t;
    double beta_value;

    if(!algorithm_id){ sprintf(filename,"data/correlation_%d_MH.dat",bin_number); }
    else             { sprintf(filename,"data/correlation_%d_SW.dat",bin_number); }
    FILE *f = fopen(filename,"w");

    for(beta_value = 0.0f; beta_value <= 1.0f; beta_value += 1.0f / n ){
        double *binned_data = get_binned_data(algorithm_id, beta_value, bin_number, func);
        for(t = 0; t < bin_number; t++){
            fprintf(f,"%f\n",binned_data[t]);
        }
    }
    fclose(f);
    free(binned_data);

    printf("Written to: %s\n",filename);
}

int main(){

    return 0;
}
