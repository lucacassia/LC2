#include"ising.h"

int get_bin_size(int ID)
{
    if(ID == 0) return 1000;
    if(ID == 1) return 50;
    return 0;
}

int main ( int argc, char *argv[] )
{
    if( argc < 2 ){
        printf( "usage: %s <input.bin> [<input.bin>]\n", argv[0] );
        return 0;
    }
    int i;
    for(i = 1; i < argc; i++){
        raw storage[2];
        FILE *fin;

        if( !(fin = fopen(argv[i], "rb") ) ){
            printf("Error opening file: %s\n", argv[i]);
            break;
        }

        storage[0] = load_data(fin,0,1000);
        storage[1] = load_data(fin,2,1000);

        char output[50];
        sprintf(output, "data/%d_%s_%d.obs", storage[0].l, storage[0].algorithm, storage[0].size );
        FILE *fout = fopen(output,"a");

        int t;
        double beta_value = storage[0].b;
        double n_bins = storage[0].size / get_bin_size(storage[0].id);
        double *binned_data[2];
        binned_data[0] = jackknife(storage[0].data, storage[0].size, get_bin_size(storage[0].id) );  raw_close(&storage[0]);
        binned_data[1] = jackknife(storage[1].data, storage[1].size, get_bin_size(storage[1].id) );  raw_close(&storage[1]);

        double mean[2], error[2];
        mean[0] = mean[1] = error[0] = error[1] = 0.0f;
        for(t = 0; t < n_bins; t++){
            mean[0] += binned_data[0][t];
            mean[1] += binned_data[1][t];
        }
        mean[0] /= n_bins;
        mean[1] /= n_bins;
        for(t = 0; t < n_bins; t++){
            error[0] += (binned_data[0][t]-mean[0])*(binned_data[0][t]-mean[0]);
            error[1] += (binned_data[1][t]-mean[1])*(binned_data[1][t]-mean[1]);
        }
        error[0] = sqrt( error[0] * (n_bins-1) / n_bins );
        error[1] = sqrt( error[1] * (n_bins-1) / n_bins );
        fprintf(fout, "%e\t%e\t%e\t%e\t%e\n", beta_value, mean[0], error[0], mean[1], error[1]);

        free(binned_data[0]);
        free(binned_data[1]);

        fclose(fout);
        printf("Written to: %s\tbeta = %f\n", output, beta_value);
    }
    return 0;
}

