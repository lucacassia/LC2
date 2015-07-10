#include"ising.h"

int main ( int argc, char *argv[] )
{
    if( argc < 2 ){
        printf( "usage: %s <input.bin> [<input.bin>]\n", argv[0] );
        return 0;
    }
    int i;
    for(i = 1; i < argc; i++){

        /* read from input */
        FILE *fin;
        if( !(fin = fopen(argv[i], "rb") ) ){
            printf("Error opening file: %s\n", argv[i]);
            break;
        }

        raw storage[2];
        storage[0] = load_data(fin,0,1000);     /* e */
        storage[1] = load_data(fin,1,1000);     /* m */

        int t;
        int lattice_size = storage[0].l;
        int bin_size = get_bin_size(storage[0].id, lattice_size);
        double beta_value = storage[0].b;
        double n_bins = storage[0].size / bin_size;
        double *binned_data[2], mean[2], variance[2];
        char output[50];
        sprintf(output, "data/%d_%s_%d.obs", lattice_size, storage[0].algorithm, storage[0].size );

        /* mean */
        binned_data[0] = jackknife(storage[0].data, storage[0].size, bin_size );
        binned_data[1] = jackknife(storage[1].data, storage[1].size, bin_size );

        mean[0] = 0.0f;
        mean[1] = 0.0f;
        for(t = 0; t < n_bins; t++){
            mean[0] += binned_data[0][t];
            mean[1] += binned_data[1][t];
        }
        mean[0] /= n_bins;
        mean[1] /= n_bins;

        /* variance */
        for(t = 0; t < storage[0].size; t++){
            storage[0].data[t] = (storage[0].data[t]-mean[0])*(storage[0].data[t]-mean[0]);
            storage[1].data[t] = (storage[1].data[t]-mean[1])*(storage[1].data[t]-mean[1]);
        }

        free(binned_data[0]);   binned_data[0] = jackknife(storage[0].data, storage[0].size, bin_size );    raw_close(&storage[0]);
        free(binned_data[1]);   binned_data[1] = jackknife(storage[1].data, storage[1].size, bin_size );    raw_close(&storage[1]);

        variance[0] = variance[1] = 0.0f;
        for(t = 0; t < n_bins; t++){
            variance[0] += binned_data[0][t];
            variance[1] += binned_data[1][t];
        }
        free(binned_data[0]);
        free(binned_data[1]);

        /* write to output */
        FILE *fout = fopen(output,"a");
        fprintf(fout, "%e\t", beta_value );
        fprintf(fout, "%e\t%e\t", mean[0], beta_value * beta_value * lattice_size * lattice_size * variance[0] );
        fprintf(fout, "%e\t%e\n", mean[1], beta_value * lattice_size * lattice_size * variance[1] );
        fclose(fout);

        printf("Written to: %s\t\tβ -> %f\n", output, beta_value);
    }
    return 0;
}

