#include"ising.h"

void plot_correlation(void (*algorithm)(int), int bin_number, int n){

    int t;
    double beta_value;
    char filename[50];
    if(algorithm == MH){ sprintf(filename,"data/correlation_%d_MH.dat",bin_number); }
    if(algorithm == SW){ sprintf(filename,"data/correlation_%d_SW.dat",bin_number); }
    FILE *f = fopen(filename,"w");

    for(beta_value = 0.0f; beta_value <= 1.0f; beta_value += 1.0f / n ){
        double *binned_data = get_binned_data(algorithm, beta_value, bin_number, func);
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
